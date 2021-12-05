#ifndef TASK_H
#define TASK_H

#include "State.h"
namespace car
{

class Task
{
public:
    Task(State* inState, int inFrameLevel, bool inIsLocated) : state(inState), frameLevel(inFrameLevel), isLocated(inIsLocated){};
    
    bool isLocated;
    int frameLevel;
    State* state;
};

}//namespace car

#endif