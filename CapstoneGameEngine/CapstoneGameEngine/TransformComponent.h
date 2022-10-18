#pragma once
#include "Component.h"
#include "Matrix.h"
#include "Quaternion.h"
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
	~TransformComponent();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render() const;
	Vec3 GetPosition() { return pos; }
	Vec3 GetScale() { return scale; }
	Quaternion GetQuaternion() { return orientation; }
	Matrix4 GetTransformMatrix() const;
	void SetTransform(Vec3 pos_, Quaternion orientation_, Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f)) {
		pos = pos_;
		orientation = orientation_;
		scale = scale_;
	}
	void SetParent(Ref<Component> parent_) { parent = parent_; }
};

