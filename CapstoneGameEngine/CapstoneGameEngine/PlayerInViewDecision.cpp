#include "PlayerInViewDecision.h"

#include "Character.h"
#include "VMath.h"
#include "Ray.h"
#include "ShapeComponent.h"

using namespace MATH;


bool PlayerInViewDecision::testValue()
{
	Ref<Actor> target = owner->getScene()->game->getPlayer();
	Ref<Actor> pickedActor;

	Vec3 ray_worldStart = owner->GetComponent<KinematicBody>()->GetPosition();
	Vec3 ray_worldDirection = target->GetComponent<TransformComponent>()->GetPosition() - ray_worldStart;

	MATH::Ray ray{ ray_worldStart, ray_worldDirection };

	// Loop through all the actors and check if the ray has collided with them
	// Pick the one with the smallest positive t value
	std::string pickedActorName;
	bool haveClickedOnSomething = false;
	GEOMETRY::RayIntersectionInfo rayInfo;
	for (auto it : owner->getScene()->getAllActors()) {
		if (dynamic_cast<Character*>(it.second.get()) == owner) { continue; }
		GEOMETRY::RayIntersectionInfo tempRayInfo;
		Ref<Actor> actor = std::dynamic_pointer_cast<Actor>(it.second);
		Ref<TransformComponent> transformComponent = actor->GetComponent <TransformComponent>();
		if (transformComponent == nullptr) { continue; }
		Vec3 position = Vec3(transformComponent->GetPosition().x, transformComponent->GetPosition().y, 0.0f);
		Ref<ShapeComponent> shapeComponent = actor->GetComponent <ShapeComponent>();
		if (shapeComponent.get() == nullptr) { continue; }
		Matrix4 worldToObjectTransform = MMath::inverse(MMath::translate(position));
		Vec3 rayStartInObjectSpace = worldToObjectTransform * ray.start;
		Vec3 rayDirInObjectSpace = worldToObjectTransform.multiplyWithoutDividingOutW(Vec4(ray.dir, 0.0f));
		MATH::Ray rayInObjectSpace{ rayStartInObjectSpace, rayDirInObjectSpace };

		tempRayInfo = shapeComponent->shape->rayIntersectionInfo(rayInObjectSpace);
		if (tempRayInfo.isIntersected) {
			if (rayInfo.isIntersected == true && tempRayInfo.t > rayInfo.t) {
				continue;
			}
			rayInfo.isIntersected = true;
			rayInfo.t = tempRayInfo.t;
			rayInfo.intersectionPoint = tempRayInfo.intersectionPoint;
			Vec3 intersectionPoint = MMath::translate(position) * rayInfo.intersectionPoint;
			pickedActor = actor;
			pickedActorName = it.first;
		}
	}

	if (pickedActorName.compare("Player") == 0)
	{
		return true;
	}
	return false;
}