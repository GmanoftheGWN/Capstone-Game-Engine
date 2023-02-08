#ifndef KINEMATIC_ARRIVE_H
#define KINEMATIC_ARRIVE_H

#include "Vector.h"
#include "VMath.h"
#include "Actor.h"
#include "SteeringBehaviour.h"
#include "KinematicSteeringOutput.h"

class KinematicArrive : public SteeringBehaviour
{
protected:
	Ref<Actor> target;
	float radius;
	float timeToTarget;

public:
	KinematicArrive(Ref<Actor> character_, Ref<Actor> target_, float radius_);
	virtual ~KinematicArrive();
	virtual SteeringOutput* getSteering();
	virtual KinematicSteeringOutput* getKinematicSteering();

};

#endif // KinematicArrive.h

