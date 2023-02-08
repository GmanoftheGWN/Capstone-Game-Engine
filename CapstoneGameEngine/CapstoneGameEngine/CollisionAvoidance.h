#ifndef COLLISION_AVOIDANCE_H
#define COLLISION_AVOIDANCE_H

#include "SteeringBehaviour.h"
#include "Seek.h"
#include <Vector>

class CollisionAvoidance : public Seek
{
protected:
	std::vector<Ref<Actor>> targets;
	float radius;
public:
	CollisionAvoidance(Ref<Actor> character_, std::vector<Ref<Actor>> targets_);
	virtual ~CollisionAvoidance();
	virtual SteeringOutput* getSteering();
};

#endif //COLLISION_AVOIDANCE_H

