#include "StaticBody.h"
#include "QMath.h"

void StaticBody::Update(float deltaTime, KinematicSteeringOutput* steering) {
	//Update using the base class
	TransformComponent::Update(deltaTime);
	newOrientation();

	//then deal with steering
	vel = steering->velocity;
	rotation = steering->rotation;

	//clip to max speed
	if (VMath::mag(vel) > maxSpeed) {
		vel = VMath::normalize(vel) * maxSpeed;
	}

	//clip to max rotation speed
	if (rotation > maxRotation) {
		rotation = maxRotation;
	}
}

void StaticBody::newOrientation() {
	if (VMath::mag(vel) > 0.0f) {
		orientation = QMath::angleAxisRotation(90.0f, Vec3(1.0f, 0.0f, 0.0f)) * QMath::angleAxisRotation(-90.0f, Vec3(0.0f, 0.0f, 1.0f)) * QMath::angleAxisRotation((atan2(vel.y, vel.x) * 180 / M_PI), Vec3(0.0f, 0.0f, 1.0f));
		//orientation = orientation * QMath::angleAxisRotation((atan2(vel.y, vel.x) * 180 / M_PI), Vec3(0.0f, 0.0f, 1.0f));
	}
}