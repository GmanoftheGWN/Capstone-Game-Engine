#include "KinematicSeek.h"
#include "TransformComponent.h"

KinematicSeek::KinematicSeek(Ref<Actor> character_, Ref<Actor> target_) {
	character = character_;
	target = target_;
	kinematicResult = new KinematicSteeringOutput();
}

KinematicSeek::~KinematicSeek() {
	if (kinematicResult) { delete kinematicResult; }
}

KinematicSteeringOutput* KinematicSeek::getKinematicSteering() {
	kinematicResult->velocity = target->GetComponent<TransformComponent>()->GetPosition() - character->GetComponent<TransformComponent>()->GetPosition();

	//go full speed along this direction
	kinematicResult->velocity = VMath::normalize(kinematicResult->velocity);
	kinematicResult->velocity = character->GetComponent<TransformComponent>()->getMaxSpeed() * kinematicResult->velocity;

	kinematicResult->rotation = 0.0f;
	return kinematicResult;

}

SteeringOutput* KinematicSeek::getSteering() {
	return nullptr;
}