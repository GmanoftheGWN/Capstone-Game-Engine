#include "KinematicArrive.h"
#include "TransformComponent.h"

KinematicArrive::KinematicArrive(Ref<Actor> character_, Ref<Actor> target_, float radius_) {
	character = character_;
	target = target_;
	radius = radius_;
	timeToTarget = 0.9f;
	kinematicResult = new KinematicSteeringOutput();
}

KinematicArrive::~KinematicArrive() {
	if (result) { delete result; }
}

KinematicSteeringOutput* KinematicArrive::getKinematicSteering() {
	kinematicResult->velocity = target->GetComponent<TransformComponent>()->GetPosition() - character->GetComponent<TransformComponent>()->GetPosition();

	if (VMath::mag(kinematicResult->velocity) == 0.0f) {
		kinematicResult->velocity = Vec3(0.0f,0.0f,0.0f);
	}
	else if (VMath::mag(kinematicResult->velocity) < radius) {
		kinematicResult->velocity /= timeToTarget;
		//std::cout << VMath::mag(result->velocity) << std::endl;
	}
	else {
		kinematicResult->velocity = VMath::normalize(kinematicResult->velocity);
		kinematicResult->velocity *= character->GetComponent<TransformComponent>()->getMaxSpeed();
	}

	kinematicResult->rotation = 0.0f;
	return kinematicResult;

}

SteeringOutput* KinematicArrive::getSteering() {
	return nullptr;
}