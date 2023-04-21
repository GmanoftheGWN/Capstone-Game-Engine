#pragma once
#include "Component.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "SteeringOutput.h"

using namespace MATH;
class TransformComponent : public Component {
protected:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	Quaternion orientation;
	float rotation;			// rotating at this speed (radians per second?)
	float angular;          // angular acceleration
	float maxSpeed;
	float maxAcceleration;
	float maxRotation;
	float maxAngular;
	float radius;
	Vec3 scale;

public:
	TransformComponent(Ref<Component> parent_);
	TransformComponent(Ref<Component> parent_, Vec3 pos_, Quaternion orientation_, Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f));
	TransformComponent(Ref<Component> parent_, Vec3 pos_, Quaternion orientation_
		, Vec3 vel_
		, Vec3 accel_
		, float mass_
		, float radius_
		, float rotation_
		, float angular_
		, float maxSpeed_
		, float maxAcceleration_
		, float maxRotation_
		, float maxAngular_
	    , Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f));
	~TransformComponent();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime_);
	void Update(const float deltaTime_, SteeringOutput* steering_);
	void ApplyForce(Vec3 force_) { accel = force_ / mass; }
	Vec3 GetPosition() { return pos; }
	void SetPosition(Vec3 pos_) { pos = pos_; }
	Vec3 getVel() { return vel; }
	void SetVel(Vec3 vel_) { vel = vel_; }
	Vec3 getAccel() { return accel; }
	void setAccel(Vec3 accel_) { accel = accel_; }
	float getMass() { return mass; }
	Quaternion getOrientation() { return orientation; }
	float getRotation() { return rotation; }
	float getAngular() { return angular; }
	float getMaxSpeed() { return maxSpeed; }
	float getMaxAcceleration() { return maxAcceleration; }
	void setMaxAcceleration(float maxAcceleration_) { maxAcceleration = maxAcceleration_; }
	float getMaxRotation() { return maxRotation; }
	float getMaxAngular() { return maxAngular; }
	Vec3 GetScale() { return scale; }
	Quaternion GetQuaternion() { return orientation; }
	Matrix4 GetTransformMatrix() const;
	void SetTransform(Vec3 pos_, Quaternion orientation_, Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f)) {
		pos = pos_;
		orientation = orientation_;
		scale = scale_;
	}
	void SetParent(Ref<Component> parent_) { parent = parent_; }
	void Render() const;

	int* physxID;
};

