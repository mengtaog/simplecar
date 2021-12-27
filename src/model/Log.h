#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include "State.h"
#include <time.h>
#include <stack>
#include "OverSequence.h"
#include "AigerModel.h"
namespace car
{

class Log
{
public:
    Log(std::string outPath, int inTimelimit, AigerModel* model) : m_model(model)
    {
        m_res.open(outPath + ".res");
        m_log.open(outPath + ".log");
        m_timelimit = static_cast<double>(inTimelimit);
        lastState = nullptr;
        m_begin = clock();
    }

    ~Log()
    {
        m_res.close();
        m_log.close();
    }

    void PrintFramesInfo(OverSequence& sequence)
    {
        m_log<<"Frame "<<sequence.GetLength()-1<<std::endl;
        for (int i = 0; i < sequence.GetLength(); ++i)
        {
            m_log<<sequence[i].size()<<" ";
        }
        m_log<<std::endl;
    }

    void PrintCounterExample(int badNo)
    {
        
        m_res <<"1"<<std::endl<<"b"<<badNo<<std::endl;
        if (lastState == nullptr)
        {
            for (int i = 0; i < m_model->GetNumLatches(); ++i)
            {
                m_res<<"0";
            }
            m_res<<std::endl;
            for (int i = 0; i < m_model->GetNumInputs(); ++i)
            {
                m_res<<"0";
            }
            m_res<<std::endl;
        }
        else
        {
            std::stack<State*> trace;
            State* state = lastState;
            while (state != nullptr)
            {
                trace.push(state);
                state = state->preState;
            }
            m_res << trace.top()->GetValueOfLatches()<<std::endl;
            //m_res << trace.top()->GetValueOfInputs()<<std::endl;
            trace.pop();
            while(!trace.empty())
            {
                m_res<<trace.top()->GetValueOfInputs()<<std::endl;
                trace.pop();
            }
        }
        m_res<<"."<<std::endl;
    }

    void PrintSafe(int badNo)
    {
        m_res <<"0"<<std::endl<<"b"<<badNo<<std::endl<<"."<<std::endl;
    }

    void PrintUcNums(std::vector<int> &uc, OverSequence& sequence)
    {
        m_res<<"UNSAT"<<std::endl;
        for (int i = 0; i < uc.size(); ++i)
        {
            m_res<<uc[i]<<" ";
        }
        m_res<<std::endl<<"Frame:\t";
        for (int i = 0; i < sequence.GetLength(); ++i)
        {
            m_res<<sequence[i].size()<<" ";
        }
        m_res<<std::endl;
    }

    void PrintSAT(std::vector<int>& vec, int frameLevel)
    {
        m_res<<"----------------------"<<std::endl;
        m_res<<"SAT, frameLevel: "<<frameLevel<<std::endl;
        for (int i = 0; i < vec.size(); ++i)
        {
            m_res<<vec[i]<<" ";
        }
        m_res<<std::endl;
    }

    void PrintStatistics()
    {
        m_log<<"MainSolverCalls:\t"<<m_mainSolverCalls<<std::endl;
        m_log<<"MainSolver takes:\t"<<m_mainSolverTime<<" seconds"<<std::endl;
        m_log<<"InvSolver takes:\t"<<m_invSolverTime<<" seconds"<<std::endl;
        m_log<<"GetNewLevel Procedure takes:\t"<<m_getNewLevelTime<<" seconds"<<std::endl;
        m_log<<"Update uc takes:\t"<<m_updateUcTime<<" seconds"<<std::endl<<std::endl;
        m_log<<"Total Time:\t"<<static_cast<double>(clock()-m_begin)/CLOCKS_PER_SEC<<" seconds"<<std::endl;
    }

    void ResetClock()
    {
        m_begin = clock();
        m_mainSolverTime = 0;
        m_mainSolverCalls = 0;
        m_invSolverCalls = 0;
        m_mainSolverTime = 0;
        m_invSolverTime = 0;
        m_getNewLevelTime = 0;
        m_updateUcTime = 0;
    }

    void Timeout()
    {
        PrintStatistics();
        exit(0);
    }

    bool IsTimeout()
    {
        clock_t current = clock();
	    double minutes = static_cast<double>(current - m_begin) / (CLOCKS_PER_SEC * 60);
        return minutes > m_timelimit;
    }

    void Tick()
    {
        m_tick = clock();
    }

    void StatMainSolver()
    {
        m_mainSolverTime += static_cast<double>(clock() - m_tick)/CLOCKS_PER_SEC;
        m_mainSolverCalls++;
    }

    void StatInvSolver()
    {
        m_invSolverTime += static_cast<double>(clock() - m_tick)/CLOCKS_PER_SEC;
    }

    void StatGetNewLevel()
    {
        m_getNewLevelTime += static_cast<double>(clock() - m_tick)/CLOCKS_PER_SEC;
    }

    void StatUpdateUc()
    {
        m_updateUcTime += static_cast<double>(clock() - m_tick)/CLOCKS_PER_SEC;
    }

    State* lastState;
    std::ofstream m_res;
private:
    int m_mainSolverCalls = 0;
    int m_invSolverCalls = 0;
    double m_mainSolverTime = 0;
    double m_invSolverTime = 0;
    double m_getNewLevelTime = 0;
    double m_updateUcTime = 0;
    double m_timelimit = 0;
    AigerModel* m_model;
    clock_t m_tick;
    clock_t m_begin;
    
    std::ofstream m_log;
    
};

}//namespace car

#endif