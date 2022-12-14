#include "Character.h"

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;
	Actor::OnCreate();
	
	return true;
}

void Character::Update(float deltaTime)
{
	// create a new overall steering output
	KinematicSteeringOutput* steering;
	steering = new KinematicSteeringOutput();

	// using the target, calculate and set values in the overall steering output
	steerToSeekTarget(steering);

	// apply the steering to the equations of motion
	this->GetComponent<KinematicBody>()->Update(deltaTime, steering);

	// clean up memory
	// (delete only those objects created in this function)
	if (steering) {
		delete steering;
	}
}

void Character::steerToSeekTarget(KinematicSteeringOutput* steering) {
	vector<KinematicSteeringOutput*> steering_outputs;

	if(this->GetComponent<FollowAPath>()) { 
		steering_outputs.push_back(this->GetComponent<FollowAPath>()->getKinematicSteering()); 
	}

	for (unsigned i = 0; i < steering_outputs.size(); i++) {
		if (steering_outputs[i]) {
			*steering += *steering_outputs[i];
		}
	}
}

void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render()
{
	
}