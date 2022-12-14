#ifndef KINEMATIC_SEEK_H
#define KINEMATIC_SEEK_H

#include "Vector.h"
#include "VMath.h"
#include "Actor.h"
#include "KinematicSteeringOutput.h"
#include "SteeringBehaviour.h"

class KinematicSeek : public SteeringBehaviour
{
private:
	KinematicSteeringOutput* kinematicResult;
	Ref<Actor> character;
	Ref<Actor> target;

public:
	KinematicSeek(Ref<Actor> character_, Ref<Actor> target_);
	virtual ~KinematicSeek();
	virtual SteeringOutput* getSteering();
	KinematicSteeringOutput* getKinematicSteering();

};

#endif // KinematicSeek.h
