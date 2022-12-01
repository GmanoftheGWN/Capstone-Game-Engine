#include "SteeringBehaviour.h"

SteeringBehaviour::SteeringBehaviour() : Component(nullptr) {
	result = new SteeringOutput();
	kinematicResult = new KinematicSteeringOutput();
	character = nullptr;
}

SteeringBehaviour::~SteeringBehaviour()
{
}

bool SteeringBehaviour::OnCreate() { return false; }
void SteeringBehaviour::OnDestroy() {}
void SteeringBehaviour::Update(const float deltaTime_) {}
void SteeringBehaviour::Render()const {}