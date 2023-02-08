#ifndef STEERING_BEHAVIOUR_H
#define STEERING_BEHAVIOUR_H

#include "VMath.h"
#include "Actor.h"
#include "KinematicBody.h"
#include "SteeringOutput.h"
#include "KinematicSteeringOutput.h"

class SteeringBehaviour : public Component
{
protected:
	SteeringOutput* result;
	KinematicSteeringOutput* kinematicResult;
	Ref<Actor> character;
public:
	SteeringBehaviour();
	virtual SteeringOutput* getSteering() = 0;
	virtual KinematicSteeringOutput* getKinematicSteering() = 0;
	virtual ~SteeringBehaviour();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render()const;
};

#endif //STEERING_BEHAVIOUR_H
