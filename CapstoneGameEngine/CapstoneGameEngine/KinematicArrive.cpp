#include "KinematicArrive.h"
#include "TransformComponent.h"

KinematicArrive::KinematicArrive(Ref<Actor> character_, Ref<Actor> target_, float radius_) {
	character = character_;
	target = target_;
	radius = radius_;
	timeToTarget = 0.9f;
	result = new KinematicSteeringOutput();
}

KinematicArrive::~KinematicArrive() {
	if (result) { delete result; }
}

KinematicSteeringOutput* KinematicArrive::getSteering() {
	result->velocity = target->GetComponent<TransformComponent>()->GetPosition() - character->GetComponent<TransformComponent>()->GetPosition();

	if (VMath::mag(result->velocity) == 0.0f) {
		result->velocity = Vec3(0.0f,0.0f,0.0f);
	}
	else if (VMath::mag(result->velocity) < radius) {
		result->velocity /= timeToTarget;
		//std::cout << VMath::mag(result->velocity) << std::endl;
	}
	else {
		result->velocity = VMath::normalize(result->velocity);
		result->velocity *= character->GetComponent<TransformComponent>()->getMaxSpeed();
	}

	result->rotation = 0.0f;
	return result;

}