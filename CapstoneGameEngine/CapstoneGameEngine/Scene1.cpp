#include <glew.h>
#include <glm/ext.hpp>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene1.h"
#include "MMath.h"
#include "QMath.h"
#include "Actor.h"
#include "CameraActor.h"
#include "LightActor.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "MaterialComponent.h"
#include "Debug.h"

Scene1::Scene1() {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {
	Debug::Info("Deleted Scene1: ", __FILE__, __LINE__);
	OnDestroy();
}

bool Scene1::OnCreate() {
	Debug::Info("Loading assets Scene1: ", __FILE__, __LINE__);

	assetManager = std::make_unique<AssetManager>(SceneManager::SCENE_NUMBER::SCENE1);

	AddActor<CameraActor>("Camera", nullptr, assetManager->GetAsset<CameraActor>("Camera"));

	AddActor<LightActor>("Light", nullptr, assetManager->GetAsset<LightActor>("Light"));

	AddActor<Actor>("Checkerboard", nullptr, assetManager->GetAsset<Actor>("Checkerboard"));

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//Messing around with adding the checkers I now see why the default copy constructor is deleted
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	Ref<Actor> redChecker;
	Ref<Actor> redCheckerAsset = assetManager->GetAsset<Actor>("RedChecker");
	for (int i = 0; i < 12; i++) {
		std::string checkerName = "RedChecker";
		std::string index = std::to_string(i);
		redChecker = std::make_shared<Actor>(nullptr);
		redChecker->AddComponent<MeshComponent>(redCheckerAsset->GetComponent<MeshComponent>());
		redChecker->AddComponent<MaterialComponent>(redCheckerAsset->GetComponent<MaterialComponent>());
		redChecker->AddComponent<ShaderComponent>(redCheckerAsset->GetComponent<ShaderComponent>());
		if (i < 4) {
			redChecker->AddComponent<TransformComponent>(GetActor<Actor>("Checkerboard"), Vec3(-4.4f + 2.5f * i, -4.35f, 0.0f), Quaternion(), Vec3(0.15f, 0.15f, 0.15f));
		}
		else if (i < 8) {
			redChecker->AddComponent<TransformComponent>(GetActor<Actor>("Checkerboard"), Vec3(-3.15f + 2.5f * (i - 4.0f), -3.1f, 0.0f), Quaternion(), Vec3(0.15f, 0.15f, 0.15f));
		}
		else if (i < 12) {
			redChecker->AddComponent<TransformComponent>(GetActor<Actor>("Checkerboard"), Vec3(-4.4f + 2.5f * (i - 8.0f), -1.85f, 0.0f), Quaternion(), Vec3(0.15f, 0.15f, 0.15f));
		}
		AddActor<Actor>(checkerName.append(index), GetActor<Actor>("Checkerboard"), redChecker);
	}

	Ref<Actor> blackChecker;
	Ref<Actor> blackCheckerAsset = assetManager->GetAsset<Actor>("BlackChecker");
	for (int i = 0; i < 12; i++) {
		std::string checkerName = "BlackChecker";
		std::string index = std::to_string(i);
		blackChecker = std::make_shared<Actor>(nullptr);
		blackChecker->AddComponent<MeshComponent>(blackCheckerAsset->GetComponent<MeshComponent>());
		blackChecker->AddComponent<MaterialComponent>(blackCheckerAsset->GetComponent<MaterialComponent>());
		blackChecker->AddComponent<ShaderComponent>(blackCheckerAsset->GetComponent<ShaderComponent>());
		if (i < 4) {
			blackChecker->AddComponent<TransformComponent>(GetActor<Actor>("Checkerboard"), Vec3(-3.15f + 2.5f * i, 4.35f, 0.0f), Quaternion(), Vec3(0.15f, 0.15f, 0.15f));
		}
		else if (i < 8) {
			blackChecker->AddComponent<TransformComponent>(GetActor<Actor>("Checkerboard"), Vec3(-4.4f + 2.5f * (i - 4.0f), 3.1f, 0.0f), Quaternion(), Vec3(0.15f, 0.15f, 0.15f));
		}
		else if (i < 12) {
			blackChecker->AddComponent<TransformComponent>(GetActor<Actor>("Checkerboard"), Vec3(-3.15f + 2.5f * (i - 8.0f), 1.85f, 0.0f), Quaternion(), Vec3(0.15f, 0.15f, 0.15f));
		}
		AddActor<Actor>(checkerName.append(index), GetActor<Actor>("Checkerboard"), blackChecker);
	}

	return true;
}

void Scene1::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	actorContainer.clear();
}

void Scene1::HandleEvents(const SDL_Event& sdlEvent) {
	Ref<CameraActor> camera = GetActor<CameraActor>("Camera");
	Ref<TransformComponent> cameraTransform = camera->GetComponent<TransformComponent>();
	Ref<Actor> checkerboard = GetActor<Actor>("Checkerboard");
	Ref<TransformComponent> checkerboardTransform = checkerboard->GetComponent<TransformComponent>();
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			cameraTransform->SetTransform(cameraTransform->GetPosition() + Vec3(-1.0f, 0.0f, 0.0f), cameraTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			cameraTransform->SetTransform(cameraTransform->GetPosition() + Vec3(1.0f, 0.0f, 0.0f), cameraTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP) {
			cameraTransform->SetTransform(cameraTransform->GetPosition() + Vec3(0.0f, 0.0f, 1.0f), cameraTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN) {
			cameraTransform->SetTransform(cameraTransform->GetPosition() + Vec3(0.0f, 0.0f, -1.0f), cameraTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) {
			checkerboardTransform->SetTransform(checkerboardTransform->GetPosition() + Vec3(0.0f, 0.0f, -1.0f), checkerboardTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			checkerboardTransform->SetTransform(checkerboardTransform->GetPosition() + Vec3(-1.0f, 0.0f, 0.0f), checkerboardTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S) {
			checkerboardTransform->SetTransform(checkerboardTransform->GetPosition() + Vec3(0.0f, 0.0f, 1.0f), checkerboardTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			checkerboardTransform->SetTransform(checkerboardTransform->GetPosition() + Vec3(1.0f, 0.0f, 0.0f), checkerboardTransform->GetQuaternion());
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_E) {
			checkerboardTransform->SetTransform(checkerboardTransform->GetPosition(), checkerboardTransform->GetQuaternion() * QMath::angleAxisRotation(-2.0f, Vec3(0.0f, 1.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Q) {
			checkerboardTransform->SetTransform(checkerboardTransform->GetPosition(), checkerboardTransform->GetQuaternion() * QMath::angleAxisRotation(2.0f, Vec3(0.0f, 1.0f, 0.0f)));
		}
		camera->UpdateViewMatrix();
		break;
	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONDOWN:
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}
}

void Scene1::Update(const float deltaTime) {
	
}

void Scene1::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& actor : actorContainer) {
		if (actor.second->GetComponent<ShaderComponent>()) {
			glUseProgram(actor.second->GetComponent<ShaderComponent>()->GetProgram());
			glUniformMatrix4fv(actor.second->GetComponent<ShaderComponent>()->GetUniformID("modelMatrix"), 1, GL_FALSE, actor.second->GetComponent<TransformComponent>()->GetTransformMatrix());
			glBindTexture(GL_TEXTURE_2D, actor.second->GetComponent<MaterialComponent>()->getTextureID());
			actor.second->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);
		}
	}

	glBindBuffer(GL_UNIFORM_BUFFER, GetActor<CameraActor>("Camera")->GetMatricesID());
	glBindBuffer(GL_UNIFORM_BUFFER, GetActor<LightActor>("Light")->GetLightDataID());

	glUseProgram(0);
}