#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include "State.h"
#include <stack>
namespace car
{

class Log
{
public:
    Log(std::string outPath)
    {
        m_log.open(outPath);
    }
    ~Log()
    {
        m_log.close();
    }
    void PrintCounterExample(int badNo)
    {
        if (lastState == nullptr)
        {
            return;
        }
        m_log <<"1"<<std::endl<<"b"<<badNo<<std::endl;
        std::stack<State*> trace;
        State* state = lastState;
        while (state != nullptr)
        {
            trace.push(state);
            state = state->preState;
        }
        m_log << trace.top()->GetValueOfLatches()<<std::endl;
        m_log << trace.top()->GetValueOfInputs()<<std::endl;
        trace.pop();
        while(!trace.empty())
        {
            m_log<<trace.top()->GetValueOfInputs()<<std::endl;
            trace.pop();
        }
        m_log<<"."<<std::endl;
    }

    void PrintSafe(int badNo)
    {
        m_log <<"0"<<std::endl<<"b"<<badNo<<std::endl<<"."<<std::endl;
    }

    State* lastState;

private:
    std::ofstream m_log;
    
};

}//namespace car

#endif