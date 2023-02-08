#include "CollisionAvoidance.h"

CollisionAvoidance::CollisionAvoidance(Ref<Actor> character_, std::vector<Ref<Actor>> targets_) : Seek{character_, nullptr}, targets(targets_), radius(1.0f) {
}

CollisionAvoidance::~CollisionAvoidance()
{
}

SteeringOutput* CollisionAvoidance::getSteering() {
    float shortestTime = INFINITY;
    Ref<Actor> firstTarget = nullptr;
    float firstMinSeparation;
    float firstDistance;
    Vec3 firstRelativePos;
    Vec3 firstRelativeVel;

    for (auto& target : targets) {
        Vec3 relativePos = target->GetComponent<TransformComponent>()->GetPosition() - character->GetComponent<TransformComponent>()->GetPosition();
        Vec3 relativeVel = target->GetComponent<TransformComponent>()->getVel() - character->GetComponent<TransformComponent>()->getVel();
        float relativeSpeed = VMath::mag(relativeVel);
        float timeToCollision = VMath::dot(relativePos, relativeVel) / (relativeSpeed * relativeSpeed);

        float distance = VMath::mag(relativePos);
        float minSeparation = distance - relativeSpeed * shortestTime;
        if (minSeparation > 2 * radius) {
            continue;
        }
        if (timeToCollision > 0 && timeToCollision < shortestTime) {
            shortestTime = timeToCollision;
            firstTarget = target;
            firstMinSeparation = minSeparation;
            firstDistance = distance;
            firstRelativePos = relativePos;
            firstRelativeVel = relativeVel;
        }
    }

    if (!firstTarget) {
        return nullptr;
    }

    Vec3 relativePos;
    if (firstMinSeparation <= 0 || firstDistance < 2 * radius) {
        relativePos = firstTarget->GetComponent<TransformComponent>()->GetPosition() - character->GetComponent<TransformComponent>()->GetPosition();
    }
    else {
        relativePos = firstRelativePos + firstRelativeVel * shortestTime;
    }
   /* Seek::target = targets[0];
    SteeringOutput* steering = Seek::getSteering();*/
    SteeringOutput* steering = new SteeringOutput;
    steering->linear = VMath::normalize(relativePos) * character->GetComponent<TransformComponent>()->getMaxAcceleration();

    return steering;
}
