#include "KinematicSeek.h"
#include "TransformComponent.h"

KinematicSeek::KinematicSeek(Ref<Actor> character_, Ref<Actor> target_) {
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput();
}

KinematicSeek::~KinematicSeek() {
	if (result) { delete result; }
}

KinematicSteeringOutput* KinematicSeek::getSteering() {
	result->velocity = target->GetComponent<TransformComponent>()->GetPosition() - character->GetComponent<TransformComponent>()->GetPosition();

	//go full speed along this direction
	result->velocity = VMath::normalize(result->velocity);
	result->velocity = character->GetComponent<TransformComponent>()->getMaxSpeed() * result->velocity;

	result->rotation = 0.0f;
	return result;

}