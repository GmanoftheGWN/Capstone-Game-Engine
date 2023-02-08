#ifndef KINEMATIC_STEERING_OUTPUT_H
#define KINEMATIC_STEERING_OUTPUT_H

#include "Vector.h"

class KinematicSteeringOutput
{
public:
	MATH::Vec3 velocity;
	float rotation;

	KinematicSteeringOutput();
	KinematicSteeringOutput(MATH::Vec3 velocity_, float rotation_);
	inline const KinematicSteeringOutput operator + (const KinematicSteeringOutput& v) const {
		return KinematicSteeringOutput(velocity + v.velocity, rotation + v.rotation);
	}
	inline KinematicSteeringOutput& operator += (const KinematicSteeringOutput& v) {
		velocity += v.velocity;
		rotation += v.rotation;
		return *this;
	}
};

#endif //KinematicSteeringOutput.h

