#ifndef CLOSER_TO_PLAYER_THAN_TARGET_DECISION_H
#define CLOSER_TO_PLAYER_THAN_TARGET_DECISION_H

#include "Decision.h"

class CloserToPlayerThanTargetDecision :
    public Decision
{
public:

    CloserToPlayerThanTargetDecision(Character* owner_, DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_)
    {
        owner = owner_;
        trueNode = trueNode_;
        falseNode = falseNode_;
    }

    bool testValue();
};

#endif