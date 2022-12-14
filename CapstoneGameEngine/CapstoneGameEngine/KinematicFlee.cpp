#include "KinematicFlee.h"

KinematicFlee::KinematicFlee(Ref<Actor> character_, Ref<Actor> target_) {
	character = character_;
	target = target_;
}

KinematicFlee::~KinematicFlee()
{
}

KinematicSteeringOutput* KinematicFlee::getKinematicSteering()
{
	kinematicResult->velocity = character->GetComponent<TransformComponent>()->GetPosition() - target->GetComponent<TransformComponent>()->GetPosition();

	kinematicResult->velocity = VMath::normalize(kinematicResult->velocity);
	kinematicResult->velocity = character->GetComponent<TransformComponent>()->getMaxSpeed() * kinematicResult->velocity;

	kinematicResult->rotation = 0.0f;

	return kinematicResult;
}

SteeringOutput* KinematicFlee::getSteering() {
	return nullptr;
}