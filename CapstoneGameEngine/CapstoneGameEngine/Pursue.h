#ifndef PURSUE_H
#define PURSUE_H

#include "Seek.h"
class Pursue : public Seek
{
public:
	float prediction;
	float maxPrediction;

	Pursue(Actor* character_, Ref<Actor> target_);
	virtual ~Pursue();
	virtual SteeringOutput* getSteering();
};

#endif //PURSUE_H

