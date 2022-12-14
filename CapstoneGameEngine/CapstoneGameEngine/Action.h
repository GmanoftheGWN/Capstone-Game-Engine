#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"

enum class DECISION_TREE { SEEKER, HIDER };

enum class ACTION_SET { DO_NOTHING, PURSUE, INTERCEPT, PATH_TO_LAST_LOCATION, EVADE, FLEE_TO_SAFETY };

class Action :
    public DecisionTreeNode
{
private:
    ACTION_SET value;

public:
    Action(ACTION_SET value_) { value = value_; }
    virtual DecisionTreeNode* makeDecision();
    virtual ACTION_SET getValue() { return value; }
};

#endif
