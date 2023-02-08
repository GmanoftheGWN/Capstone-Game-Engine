#include "FollowAPath.h"
#include "TransformComponent.h"

FollowAPath::FollowAPath(Ref<Actor> character_, Ref<Actor> target_, float radius_, Path* path_) : KinematicArrive{ character_, target_, radius_ }
{
    path = path_;
}

FollowAPath::~FollowAPath()
{
}

KinematicSteeringOutput* FollowAPath::getKinematicSteering() {

    Vec3 target_position;

    if (!path) return nullptr;

    target_position = path->getCurrentNodePosition() + Vec3(0.0f,0.0f,1.25f);

    if (VMath::distance(character->GetComponent<TransformComponent>()->GetPosition(), target_position) <= radius)
    {

        // incremented for next steering request
        path->incrementCurrentNode();

    }

    target->GetComponent<TransformComponent>()->SetPosition(target_position);

    return KinematicArrive::getKinematicSteering();

}

SteeringOutput* FollowAPath::getSteering() {
    return nullptr;
}