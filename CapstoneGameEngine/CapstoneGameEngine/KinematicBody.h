#ifndef KINEMATIC_BODY_H
#define KINEMATIC_BODY_H

#include "TransformComponent.h"
#include "SteeringOutput.h"

class KinematicBody :
	public TransformComponent
{
protected:

public:
	KinematicBody() : TransformComponent{parent}
	{}

	KinematicBody(
		Ref<Component> parent_,
		Vec3 pos_, Quaternion orientation_, 
		Vec3 vel_, 
		Vec3 accel_,
		float mass_,
		float radius_,
		float rotation_ = 0.0f,
		float angular_ = 0.0f,
		float maxSpeed_ = 1.0f,
		float maxAcceleration_ = 1.0f,
		float maxRotation_ = 1.0f,
		float maxAngular_ = 1.0f
	) : TransformComponent{ parent_, pos_, orientation_, vel_, accel_, mass_
		, radius_
		, rotation_
		, angular_
		, maxSpeed_
		, maxAcceleration_
		, maxRotation_
		, maxAngular_
	}
	{}

	void Update(float deltaTime, SteeringOutput* steering);
};

#endif

