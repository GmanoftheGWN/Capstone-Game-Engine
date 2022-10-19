#ifndef STATIC_BODY_H
#define STATIC_BODY_H

#include "TransformComponent.h"
#include "KinematicSteeringOutput.h"

class StaticBody : public TransformComponent
{
private:

public:
	StaticBody(Ref<Component> parent) : TransformComponent( parent)
	{}

	StaticBody(
		Ref<Component> parent_,
		Vec3 pos_, Quaternion orientation_,
		float maxSpeed_,
		float maxRotation_,
		Vec3 scale_ = Vec3(1.0f,1.0f,1.0f)
	) : TransformComponent{ parent_, pos_, orientation_, Vec3(), Vec3(), 1.0f
		, 1.0f
		, 0.0f
		, 0.0f
		, maxSpeed_
		, 0.0f
		, maxRotation_
		, 0.0f
		, scale_
	}
	{}

	void Update(float deltaTime, KinematicSteeringOutput* steering);
	void newOrientation();
};
#endif //StaticBody.h
