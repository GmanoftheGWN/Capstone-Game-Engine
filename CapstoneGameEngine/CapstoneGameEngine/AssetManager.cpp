#include "AssetManager.h"
#include <memory>
#include <iostream>
#include <fstream>
#include "QMath.h"
#include "CameraActor.h"
#include "LightActor.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "MaterialComponent.h"
#include "Debug.h"

AssetManager::AssetManager(SceneManager::SCENE_NUMBER sceneNumber_):sceneNumber(sceneNumber_) {
	ReadManifest();
	OnCreate();
}

AssetManager::~AssetManager() {
	RemoveAllAssets();
}

bool AssetManager::OnCreate() {
	printf("AssetManager contains:\n");
	for (std::pair<std::string, Ref<Component>> a : assetCatalog) {
		printf(a.first.c_str());
		printf("\n");
		if (a.second->OnCreate() == false) {
			return false;
		}
	}
	return true;
}

void AssetManager::RemoveAllAssets() {
	Debug::Info("Clearing Asset Manager: ", __FILE__, __LINE__);
	assetCatalog.clear();
}

void AssetManager::ReadManifest() {
	Debug::Info("Asset Manager Loading Assets from XML: ", __FILE__, __LINE__);
	tinyxml2::XMLDocument doc;
	doc.LoadFile("Manifest.xml");
	bool status = doc.Error();
	if (status) {
		std::cout << doc.ErrorIDToName(doc.ErrorID()) << std::endl;
		return;
	}

	tinyxml2::XMLElement* rootData = doc.RootElement();
	if (sceneNumber == SceneManager::SCENE_NUMBER::SCENE0) {
		sceneData = rootData->FirstChildElement("Scene0");
	}
	else if (sceneNumber == SceneManager::SCENE_NUMBER::SCENE1) {
		sceneData = rootData->FirstChildElement("Scene1");
	}
	else if (sceneNumber == SceneManager::SCENE_NUMBER::AITEST) {
		sceneData = rootData->FirstChildElement("Scene0");
	}

	//Camera
	AddAsset<CameraActor>("Camera", nullptr);
	tinyxml2::XMLElement* cameraData = sceneData->FirstChildElement("Camera");
	tinyxml2::XMLElement* cameraComponent = cameraData->FirstChildElement("Component");
	tinyxml2::XMLElement* cameraLocation = cameraComponent->FirstChildElement("Location");
	tinyxml2::XMLElement* actorOrientation = cameraComponent->FirstChildElement("Orientation");
	Vec3 location;
	location.x = cameraLocation->FloatAttribute("x");
	location.y = cameraLocation->FloatAttribute("y");
	location.z = cameraLocation->FloatAttribute("z");
	
	if (actorOrientation->Attribute("type", "AngleAxis")) {
		float angle = actorOrientation->FloatAttribute("angle");
		Vec3 axis;
		axis.x = actorOrientation->FloatAttribute("axisX");
		axis.y = actorOrientation->FloatAttribute("axisY");
		axis.z = actorOrientation->FloatAttribute("axisZ");
		GetAsset<CameraActor>("Camera")->AddComponent<TransformComponent>(nullptr, location, Quaternion(QMath::angleAxisRotation(angle, axis)));
	}

	//Light
	tinyxml2::XMLElement* lightData = sceneData->FirstChildElement("Light");
	tinyxml2::XMLElement* lightLocation = lightData->FirstChildElement("Location");
	location.x = lightLocation->FloatAttribute("x");
	location.y = lightLocation->FloatAttribute("y");
	location.z = lightLocation->FloatAttribute("z");
	tinyxml2::XMLElement* diffuseColor = lightData->FirstChildElement("Diffuse");
	Vec4 color;
	color.x = diffuseColor->FloatAttribute("red");
	color.y = diffuseColor->FloatAttribute("green");
	color.z = diffuseColor->FloatAttribute("blue");
	color.w = diffuseColor->FloatAttribute("alpha");
	AddAsset<LightActor>("Light", nullptr, LightStyle::PointLight, location, color);

	//Actors
	for (tinyxml2::XMLElement* actorData = sceneData->FirstChildElement("Actor"); actorData != nullptr; actorData = actorData->NextSiblingElement("Actor")) {
		AddAsset<Actor>(actorData->Attribute("name"), nullptr);
		for (tinyxml2::XMLElement* component = actorData->FirstChildElement("Component"); component != nullptr; component = component->NextSiblingElement("Component")) {
			if (component->Attribute("name", "Transform")) {
				tinyxml2::XMLElement* actorLocation = component->FirstChildElement("Location");
				Vec3 location;
				location.x = actorLocation->FloatAttribute("x");
				location.y = actorLocation->FloatAttribute("y");
				location.z = actorLocation->FloatAttribute("z");
				tinyxml2::XMLElement* actorOrientation = component->FirstChildElement("Orientation");
				if (actorOrientation->Attribute("type", "AngleAxis")) {
					float angle = actorOrientation->FloatAttribute("angle");
					Vec3 axis;
					axis.x = actorOrientation->FloatAttribute("axisX");
					axis.y = actorOrientation->FloatAttribute("axisY");
					axis.z = actorOrientation->FloatAttribute("axisZ");
					GetAsset<Actor>(actorData->Attribute("name"))->AddComponent<TransformComponent>(nullptr, location, Quaternion(QMath::angleAxisRotation(angle, axis)));
				}
			}
			if (component->Attribute("name", "Mesh")) {
				GetAsset<Actor>(actorData->Attribute("name"))->AddComponent<MeshComponent>(nullptr, component->Attribute("filename"));
			}
			if (component->Attribute("name", "Material")) {
				GetAsset<Actor>(actorData->Attribute("name"))->AddComponent<MaterialComponent>(nullptr, component->Attribute("filename"));
			}
			if (component->Attribute("name", "Shader")) {
				GetAsset<Actor>(actorData->Attribute("name"))->AddComponent<ShaderComponent>(nullptr, component->Attribute("vertFilename"), component->Attribute("fragFilename"));
			}
		}
	}

	//Components
	for (tinyxml2::XMLElement* compnentData = sceneData->FirstChildElement("Component"); compnentData != nullptr; compnentData = compnentData->NextSiblingElement("Component")) {
		if (compnentData->Attribute("name", "Mesh")) {
			AddAsset<MeshComponent>(compnentData->Attribute("type"), nullptr, compnentData->Attribute("filename"));
		}
		if (compnentData->Attribute("name", "Material")) {
			AddAsset<MaterialComponent>(compnentData->Attribute("type"), nullptr, compnentData->Attribute("filename"));
		}
		if (compnentData->Attribute("name", "Shader")) {
			AddAsset<ShaderComponent>(compnentData->Attribute("type"), nullptr, compnentData->Attribute("vertFilename"), compnentData->Attribute("fragFilename"));
		}
	}
}