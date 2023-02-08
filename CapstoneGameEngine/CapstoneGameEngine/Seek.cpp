#include "Seek.h"

Seek::Seek(Ref<Actor> character_, Ref<Actor> target_) {
	character = character_;
	target = target_;
}

Seek::~Seek()
{
}

SteeringOutput* Seek::getSteering()
{
	result->linear = target->GetComponent<TransformComponent>()->GetPosition() - character->GetComponent<TransformComponent>()->GetPosition();

	if (VMath::mag(result->linear) > 0) {
		result->linear = VMath::normalize(result->linear) * character->GetComponent<TransformComponent>()->getMaxAcceleration();
	}

	result->angular = 0.0f;

	return result;
}
