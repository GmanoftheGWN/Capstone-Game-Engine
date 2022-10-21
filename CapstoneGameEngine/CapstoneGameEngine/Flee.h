#ifndef FLEE_H
#define FLEE_H

#include "SteeringBehaviour.h"

class Flee : public SteeringBehaviour
{
protected:
	Ref<Actor> target;

public:
	Flee(Actor* character_, Ref<Actor> target_);
	virtual ~Flee();
	virtual SteeringOutput* getSteering();
};

#endif //FLEE_H