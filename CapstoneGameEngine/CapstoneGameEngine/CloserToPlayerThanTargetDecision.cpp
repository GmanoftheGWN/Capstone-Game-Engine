#include "CloserToPlayerThanTargetDecision.h"

#include "Character.h"
#include "VMath.h"

using namespace MATH;


bool CloserToPlayerThanTargetDecision::testValue()
{
	if (VMath::distance(owner->getScene()->game->getPlayer()->GetComponent<TransformComponent>()->GetPosition(), owner->GetComponent<TransformComponent>()->GetPosition())
		< VMath::distance(dynamic_cast<AI_Test*>(owner->getScene())->nodes[dynamic_cast<AI_Test*>(owner->getScene())->safeNode]->getPos(), owner->GetComponent<TransformComponent>()->GetPosition()))
	{
		return true;
	}
	return false;
}