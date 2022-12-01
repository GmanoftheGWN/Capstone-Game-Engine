#ifndef KINEMATIC_ARRIVE_H
#define KINEMATIC_ARRIVE_H

#include "Vector.h"
#include "VMath.h"
#include "Actor.h"
#include "KinematicSteeringOutput.h"

class KinematicArrive
{
protected:
	KinematicSteeringOutput* result;
	Ref<Actor> character;
	Ref<Actor> target;
	float radius;
	float timeToTarget;

public:
	KinematicArrive(Ref<Actor> character_, Ref<Actor> target_, float radius_);
	~KinematicArrive();
	KinematicSteeringOutput* getSteering();

};

#endif // KinematicArrive.h

