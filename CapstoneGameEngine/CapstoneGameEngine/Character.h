#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "TransformComponent.h"
#include "KinematicBody.h"

using namespace std;

class Character : public Actor
{
private:
	Ref<TransformComponent> body;
	class Scene* scene;

public:
	Character(Ref<Component> parent_);
	// TODO add constructor that takes parameters for the body
	~Character()
	{
		
	};
	bool OnCreate(Scene* scene_);
	void OnDestroy() {};

	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render();

};

#endif