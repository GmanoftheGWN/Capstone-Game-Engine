#ifndef KINEMATIC_FLEE_H
#define KINEMATIC_FLEE_H

#include "SteeringBehaviour.h"

class KinematicFlee : public SteeringBehaviour
{
protected:
	Ref<Actor> target;

public:
	KinematicFlee(Ref<Actor> character_, Ref<Actor> target_);
	virtual ~KinematicFlee();
	virtual SteeringOutput* getSteering();
	virtual KinematicSteeringOutput* getKinematicSteering();
};

#endif //FLEE_H