#ifndef EVADE_H
#define EVADE_H

#include "KinematicFlee.h"
class Evade : public KinematicFlee
{
protected:
	float prediction;
	float maxPrediction;

public:
	Evade(Ref<Actor> character_, Ref<Actor> target_);
	virtual ~Evade();
	virtual SteeringOutput* getSteering();
};

#endif //EVADE_H