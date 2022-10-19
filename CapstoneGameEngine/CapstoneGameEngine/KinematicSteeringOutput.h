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
};

#endif //KinematicSteeringOutput.h

