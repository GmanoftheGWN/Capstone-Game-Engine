#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "TransformComponent.h"
#include "KinematicBody.h"
#include "SteeringBehaviour.h"
#include "Seek.h"
#include "Pursue.h"
#include "Flee.h"
#include "Evade.h"

using namespace std;

class Character : public Actor
{
private:
	class Scene* scene;

public:
    Character(): Actor(nullptr) {
        scene = nullptr;
    }

    Character(Ref<Component> parent_,
        Vec3 pos_, Quaternion orientation_,
        Vec3 vel_,
        Vec3 accel_,
        float mass_,
        float radius_,
        float rotation_,
        float angular_,
        float maxSpeed_,
        float maxAcceleration_,
        float maxRotation_,
        float maxAngular_
    ) : Actor{ parent_ }, scene(nullptr)
    {
        this->AddComponent<TransformComponent>(parent_, pos_, orientation_, vel_, accel_, mass_
            , radius_
            , rotation_
            , angular_
            , maxSpeed_
            , maxAcceleration_
            , maxRotation_
            , maxAngular_);
    }
	~Character()
	{
		
	};
	bool OnCreate(Scene* scene_);
	void OnDestroy() {};

	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render();
    void steerToSeekPlayer(SteeringOutput* steering);

};

#endif