#ifndef PURSUE_H
#define PURSUE_H

#include "Seek.h"
class Pursue : public Seek
{
protected:
	float prediction;
	float maxPrediction;

public:
	Pursue(Ref<Actor> character_, Ref<Actor> target_);
	virtual ~Pursue();
	virtual SteeringOutput* getSteering();
};

#endif //PURSUE_H

