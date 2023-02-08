#include <iostream>
#include "TransformComponent.h"
#include "QMath.h"
#include "MMath.h"
#include "Actor.h"

TransformComponent::TransformComponent(Ref<Component> parent_):Component(parent_) {
	scale = Vec3(1.0f, 1.0f, 1.0f);
	pos = Vec3(0.0f, 0.0f, 0.0f);
	orientation = Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0f));
}

TransformComponent::TransformComponent(Ref<Component> parent_, Vec3 pos_, Quaternion orientation_, Vec3 scale_) : Component(parent_),
	pos(pos_), orientation(orientation_), scale(scale_), vel(Vec3(0.0f, 0.0f, 0.0f)), accel(Vec3(0.0f, 0.0f, 0.0f)), mass(0.0f), rotation(0.0f),
	angular(0.0f), maxSpeed(5.0f), maxAcceleration(0.0f), maxRotation(0.0f), maxAngular(0.0f), radius(0.0f) {
	
}

TransformComponent::TransformComponent(Ref<Component> parent_, Vec3 pos_, Quaternion orientation_, 
	Vec3 vel_, Vec3 accel_, float mass_, float radius_, float rotation_, float angular_, float maxSpeed_, 
	float maxAcceleration_, float maxRotation_, float maxAngular_, Vec3 scale_) : Component(parent_),
	pos(pos_), orientation(orientation_)
, vel(vel_)
, accel(accel_)
, mass(mass_)
, radius(radius_)
, rotation(rotation_)
, angular(angular_)
, maxSpeed(maxSpeed_)
, maxAcceleration(maxAcceleration_)
, maxRotation(maxRotation_)
, maxAngular(maxAngular_)
, scale(scale_) {
}


TransformComponent::~TransformComponent() {
	OnDestroy();
}

bool TransformComponent::OnCreate() {
	if (isCreated) return isCreated;
	isCreated = true;
	return isCreated;
}

void TransformComponent::OnDestroy() {
	isCreated = false;
}

void TransformComponent::Update(const float deltaTime) {
	pos = pos + vel * deltaTime + accel * (0.5f * deltaTime * deltaTime);
	vel = vel + accel * deltaTime;
	// Update orientation
	orientation = QMath::angleAxisRotation(90, Vec3(1.0f, 0.0f, 0.0f)) * QMath::angleAxisRotation((rotation * deltaTime) * 360 / M_PI, Vec3(0.0f, 1.0f, 0.0f));
	rotation += angular * deltaTime;

	// Clip to maxspeed, if speed exceeds max
	if (VMath::mag(vel) > maxSpeed)
	{
		vel = VMath::normalize(vel) * maxSpeed;
	}

	// Clip to maxrotation, if needed
	if (rotation > maxRotation) rotation = maxRotation;

	// Could introduce dampening, of velocity and/or rotation, to simulate friction
	//vel -= 0.05 * vel;
	//rotation -= 0.05 * rotation;
}

void TransformComponent::Update(const float deltaTime, SteeringOutput* steering_) {
	pos = pos + vel * deltaTime + accel * (0.5f * deltaTime * deltaTime);
	vel = vel + accel * deltaTime;
	// Update orientation
	orientation = QMath::angleAxisRotation(90, Vec3(1.0f, 0.0f, 0.0f)) * QMath::angleAxisRotation((rotation * deltaTime) * 360 / M_PI, Vec3(0.0f, 1.0f, 0.0f));
	rotation += angular * deltaTime;

	// Clip to maxspeed, if speed exceeds max
	if (VMath::mag(vel) > maxSpeed)
	{
		vel = VMath::normalize(vel) * maxSpeed;
	}

	// Clip to maxrotation, if needed
	if (rotation > maxRotation) rotation = maxRotation;

	// Could introduce dampening, of velocity and/or rotation, to simulate friction
	//vel -= 0.05 * vel;
	//rotation -= 0.05 * rotation;
}

Matrix4 TransformComponent::GetTransformMatrix() const
{
	if (parent) {
		return dynamic_cast<Actor*>(parent.get())->GetComponent<TransformComponent>()->GetTransformMatrix() * MMath::translate(pos) * MMath::scale(scale) * QMath::toMatrix4(orientation);
	}
	return MMath::translate(pos) * MMath::scale(scale) * QMath::toMatrix4(orientation);
}

void TransformComponent::Render() const{}
