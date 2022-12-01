#include "Evade.h"

Evade::Evade(Ref<Actor> character_, Ref<Actor> target_) : Flee{ character_, target_ } {
	character = character_;
	target = target_;
	prediction = maxPrediction = 10.0f;
}

Evade::~Evade()
{
}

SteeringOutput* Evade::getSteering()
{
	Vec3 direction = target->GetComponent<TransformComponent>()->GetPosition() - character->GetComponent<TransformComponent>()->GetPosition();
	float distance = VMath::mag(direction);

	float speed = VMath::mag(character->GetComponent<TransformComponent>()->getVel());

	if (speed <= (distance / maxPrediction)) {
		prediction = maxPrediction;
	}
	else {
		prediction = distance / speed;
	}

	Flee::target = target;
	Flee::target->GetComponent<TransformComponent>()->SetPosition(target->GetComponent<TransformComponent>()->GetPosition() + target->GetComponent<TransformComponent>()->getVel() * prediction);

	SteeringOutput* steering = Flee::getSteering();

	Flee::target->GetComponent<TransformComponent>()->SetPosition(target->GetComponent<TransformComponent>()->GetPosition() - target->GetComponent<TransformComponent>()->getVel() * prediction);

	return steering;
}