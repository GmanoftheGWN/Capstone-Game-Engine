#ifndef SCENE_H
#define SCENE_H
#include "Actor.h"
#include "Debug.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include <unordered_map>

union SDL_Event;
class SceneManager;

class Scene{
protected:
	std::unordered_map<std::string, Ref<Actor>> actorContainer;
public:	
	SceneManager* game;

	virtual ~Scene() {}
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const = 0;
	virtual void HandleEvents(const SDL_Event &sdlEvent) = 0;

	std::unordered_map<std::string, Ref<Actor >> getAllActors() { return actorContainer; }

	template<typename ActorTemplate>
	void AddActor(std::string name, Ref<Actor> parent_, Ref<ActorTemplate> actor_) {
		if (dynamic_cast<Actor*>(actor_.get())) {
			if (Ref<TransformComponent> tc = actor_->GetComponent<TransformComponent>()) {
				tc->SetParent(parent_);
			}
		}
		actorContainer[name] = actor_;
	}

	template<typename ActorTemplate>
	Ref<ActorTemplate> GetActor(std::string name) const {
		auto id = actorContainer.find(name);
#ifdef _DEBUG
		if (id == actorContainer.end()) {
			Debug::Error("Can't find requested actor", __FILE__, __LINE__);
			return Ref<ActorTemplate>(nullptr);
		}
#endif
		return std::dynamic_pointer_cast<ActorTemplate>(id->second);
	}
	
};
#endif