#ifndef RESTARTPOLICY_H
#define RESTARTPOLICY_H


#include "State.h"
#include "Task.h"
#include<stack>
#include<memory>

namespace car
{

struct RestartPolicy
{
public:
    int threshold;
    float growthRate;
    int counter;
    State* initialState;
    bool RestartPoint()
    {

    }

    void BackTrackTo(std::stack<Task>& tasks)
    {
        
    }

    void Update()
    {
        threshold = threshold * growthRate;
        counter = 0;
    }


}


}//namespace car


#endif