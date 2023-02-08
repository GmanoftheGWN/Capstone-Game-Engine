#include "KinematicBody.h"

void KinematicBody::Update(float deltaTime, KinematicSteeringOutput* steering)
{
    //// Update position, call Update from parent class
    //// Note that would update velocity too, but the acceleration in the member object is 0.0!
    //TransformComponent::Update(deltaTime);

    //// TODO Body reaching edge of scene needs to be handled somewhere
    //// especially if implementing the flee behaviour

    //// Adjust velocity and rotation according to steering input
    //if (steering)
    //{
    //    accel = steering->linear;
    //    angular = steering->angular;
    //}

    //if (VMath::mag(accel) > maxAcceleration) {
    //    accel = VMath::normalize(accel) * maxAcceleration;
    //}

    //if (angular > maxAngular) {
    //    angular = maxAngular;
    //}

    //Update using the base class
    TransformComponent::Update(deltaTime);
   // newOrientation();

    //then deal with steering
    vel = steering->velocity;
    rotation = steering->rotation;

    //clip to max speed
    if (VMath::mag(vel) > maxSpeed) {
        vel = VMath::normalize(vel) * maxSpeed;
    }

    //clip to max rotation speed
    if (rotation > maxRotation) {
        rotation = maxRotation;
    }

}
