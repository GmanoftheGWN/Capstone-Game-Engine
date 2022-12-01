#include "Pursue.h"

Pursue::Pursue(Ref<Actor> character_, Ref<Actor> target_) : Seek{ character_, target_ } {
	character = character_;
	target = target_;
	prediction = maxPrediction = 10.0f;
}

Pursue::~Pursue()
{
}

SteeringOutput* Pursue::getSteering()
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

	Seek::target = target;
	Seek::target->GetComponent<TransformComponent>()->SetPosition(target->GetComponent<TransformComponent>()->GetPosition() + target->GetComponent<TransformComponent>()->getVel() * prediction);

	SteeringOutput* steering = Seek::getSteering();

	Seek::target->GetComponent<TransformComponent>()->SetPosition(target->GetComponent<TransformComponent>()->GetPosition() - target->GetComponent<TransformComponent>()->getVel() * prediction);

	return steering;
}