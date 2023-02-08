#ifndef CONDITION_IN_VIEW_H
#define CONDITION_IN_VIEW_H

#include "Condition.h"

class ConditionInView :
    public Condition
{
private:

public:
    ConditionInView(Character* owner_)
        : Condition{ owner_ }
    {
        
    }

    bool test();

};

#endif