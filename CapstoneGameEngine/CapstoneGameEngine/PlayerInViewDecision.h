#ifndef PLAYERINVIEWDECISION_H
#define PLAYERINVIEWDECISION_H

#include "Decision.h"

class PlayerInViewDecision :
    public Decision
{
public:

    PlayerInViewDecision(Character* owner_, DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_)
    {
        owner = owner_;
        trueNode = trueNode_;
        falseNode = falseNode_;
    }

    bool testValue();
};

#endif