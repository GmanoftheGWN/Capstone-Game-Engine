#include "KinematicSteeringOutput.h"

KinematicSteeringOutput::KinematicSteeringOutput() {
	velocity = MATH::Vec3();
	rotation = 0.0f;
}

KinematicSteeringOutput::KinematicSteeringOutput(MATH::Vec3 velocity_, float rotation_) {
	velocity = velocity_;
	rotation = rotation_;
}