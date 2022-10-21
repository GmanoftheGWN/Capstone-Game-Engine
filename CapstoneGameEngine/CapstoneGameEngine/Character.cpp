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
	SteeringOutput* steering;
	steering = new SteeringOutput();

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)
	Ref<Actor> target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	steerToSeekPlayer(steering);

	// apply the steering to the equations of motion
	this->GetComponent<KinematicBody>()->Update(deltaTime, steering);

	// clean up memory
	// (delete only those objects created in this function)
	if (steering) {
		delete steering;
	}
}

void Character::steerToSeekPlayer(SteeringOutput* steering) {
	vector<SteeringOutput*> steering_outputs;

	/*vector<Ref<Actor>> targets;
	targets.push_back(scene->game->getPlayer());
	SteeringBehaviour* steering_algorithm = new CollisionAvoidance(this, targets);*/

	/*SteeringBehaviour* steering_algorithm = new Pursue(this, scene->game->getPlayer());*/

	SteeringBehaviour* steering_algorithm = new Evade(this, scene->game->getPlayer());

	steering_outputs.push_back(steering_algorithm->getSteering());

	for (unsigned i = 0; i < steering_outputs.size(); i++) {
		if (steering_outputs[i]) {
			*steering += *steering_outputs[i];
		}
	}

	if (steering_algorithm) {
		delete steering_algorithm;
	}
}

void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render()
{
	
}