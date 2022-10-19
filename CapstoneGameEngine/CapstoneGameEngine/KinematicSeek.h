#ifndef KINEMATIC_SEEK_H
#define KINEMATIC_SEEK_H

#include "Vector.h"
#include "VMath.h"
#include "Actor.h"
#include "KinematicSteeringOutput.h"

class KinematicSeek
{
private:
	KinematicSteeringOutput* result;
	Ref<Actor> character;
	Ref<Actor> target;

public:
	KinematicSeek(Ref<Actor> character_, Ref<Actor> target_);
	~KinematicSeek();
	KinematicSteeringOutput* getSteering();

};

#endif // KinematicSeek.h
