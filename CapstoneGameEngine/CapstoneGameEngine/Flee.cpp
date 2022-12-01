#include "Flee.h"

Flee::Flee(Ref<Actor> character_, Ref<Actor> target_) {
	character = character_;
	target = target_;
}

Flee::~Flee()
{
}

SteeringOutput* Flee::getSteering()
{
	result->linear = target->GetComponent<TransformComponent>()->GetPosition() - character->GetComponent<TransformComponent>()->GetPosition();

	if (VMath::mag(result->linear) > 0) {
		result->linear = VMath::normalize(result->linear) * -character->GetComponent<TransformComponent>()->getMaxAcceleration();
	}

	result->angular = 0.0f;

	return result;
}