#ifndef SEEK_H
#define SEEK_H

#include "SteeringBehaviour.h"

class Seek : public SteeringBehaviour
{
protected:
	Ref<Actor> target;

public:
	Seek(Ref<Actor> character_, Ref<Actor> target_);
	virtual ~Seek();
	virtual SteeringOutput* getSteering();
};

#endif //SEEK_H

