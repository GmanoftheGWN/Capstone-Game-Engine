#include "Character.h"

Character::Character(Ref<Component> parent_) :Actor(parent_) {}

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;
	Actor::OnCreate();
	//// Configure and instantiate the body to use for the demo
	//if (!body)
	//{
	//	float radius = 0.2f;
	//	float orientation = 0.0f;
	//	float rotation = 0.0f;
	//	float angular = 0.0f;
	//	float maxSpeed = 4.0f;
	//	float maxAcceleration = 10.0f;
	//	float maxRotation = 2.0f;
	//	float maxAngular = 10.0f;
	//	body = std::make_shared<KinematicBody>(
	//		Vec3(10.0f, 5.0f, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
	//		radius,
	//		orientation,
	//		rotation,
	//		angular,
	//		maxSpeed,
	//		maxAcceleration,
	//		maxRotation,
	//		maxAngular
	//	);
	//}

	//if (!body)
	//{
	//	return false;
	//}

	return true;
}

void Character::Update(float deltaTime)
{
	// create a new overall steering output
	SteeringOutput* steering;
	steering = NULL;

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	// using the target, calculate and set values in the overall steering output

	// apply the steering to the equations of motion
	body->Update(deltaTime);

	// clean up memory
	// (delete only those objects created in this function)
}

void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render()
{
	
}