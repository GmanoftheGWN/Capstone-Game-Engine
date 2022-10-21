#ifndef STEERING_BEHAVIOUR_H
#define STEERING_BEHAVIOUR_H

#include "VMath.h"
#include "Actor.h"
#include "KinematicBody.h"
#include "SteeringOutput.h"

class SteeringBehaviour
{
protected:
	SteeringOutput* result;
	Actor* character;
public:
	SteeringBehaviour();
	virtual SteeringOutput* getSteering() = 0;
	~SteeringBehaviour();
};

#endif //STEERING_BEHAVIOUR_H
