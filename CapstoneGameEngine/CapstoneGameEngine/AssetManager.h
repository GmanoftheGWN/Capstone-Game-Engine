#pragma once
#include <string>
#include <iostream>
#include "tinyxml2.h"
#include <unordered_map>
#include "Component.h"
#include "Actor.h"
#include "SceneManager.h"
#include "Debug.h"

class AssetManager {
private:
	std::unordered_map<std::string, Ref<Component>> assetCatalog;

public:
	AssetManager(SceneManager::SCENE_NUMBER sceneNumber_);
	~AssetManager();

	SceneManager::SCENE_NUMBER sceneNumber;
	tinyxml2::XMLElement* sceneData;

	void ReadManifest();
	bool OnCreate();
	void RemoveAllAssets();

	template<typename AssetTemplate, typename ... Args>
	void AddAsset(const char* name, Args&& ... args_) {
		Ref<AssetTemplate> t = std::make_shared<AssetTemplate>(std::forward<Args>(args_)...);
		std::string stringName(name);
		assetCatalog[stringName] = t;
	}

	template<typename AssetTemplate>
	Ref<AssetTemplate> GetAsset(const char* name) const {
		std::string stringName(name);
		auto id = assetCatalog.find(stringName);
#ifdef _DEBUG
		if (id == assetCatalog.end()) {
			Debug::Error("Can't find requested asset", __FILE__, __LINE__);
			return Ref<AssetTemplate>(nullptr);
		}
#endif
		return std::dynamic_pointer_cast<AssetTemplate>(id->second);
	}

};

