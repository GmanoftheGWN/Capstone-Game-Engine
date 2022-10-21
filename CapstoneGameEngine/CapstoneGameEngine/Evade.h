#ifndef EVADE_H
#define EVADE_H

#include "Flee.h"
class Evade : public Flee
{
public:
	float prediction;
	float maxPrediction;

	Evade(Actor* character_, Ref<Actor> target_);
	virtual ~Evade();
	virtual SteeringOutput* getSteering();
};

#endif //EVADE_H