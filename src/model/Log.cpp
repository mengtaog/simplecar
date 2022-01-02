#include "Log.h"

namespace car
{

    void Log::PrintFramesInfo(IOverSequence* sequence)
    {
        m_log<<"Frame "<<sequence->GetLength()-1<<std::endl;
        for (int i = 0; i < sequence->GetLength(); ++i)
        {
            std::vector<std::vector<int> > frame;
            sequence->GetFrame(i, frame);
            m_log<<frame.size()<<" ";
        }
        m_log<<std::endl;
    }

    void Log::PrintCounterExample(int badNo)
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
            std::stack<std::shared_ptr<State> > trace;
            std::shared_ptr<State> state = lastState;
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

    void Log::PrintSafe(int badNo)
    {
        m_res <<"0"<<std::endl<<"b"<<badNo<<std::endl<<"."<<std::endl;
    }

    void Log::PrintUcNums(std::vector<int> &uc, IOverSequence* sequence)
    {
        m_res<<"UNSAT"<<std::endl;
        for (int i = 0; i < uc.size(); ++i)
        {
            m_res<<uc[i]<<" ";
        }
        m_res<<std::endl<<"Frame:\t";
        for (int i = 0; i < sequence->GetLength(); ++i)
        {
            std::vector<std::vector<int> > frame;
            sequence->GetFrame(i, frame);
            m_res<<frame.size()<<" ";
        }
        m_res<<std::endl;
    }

    void Log::PrintSAT(std::vector<int>& vec, int frameLevel)
    {
        m_res<<"----------------------"<<std::endl;
        m_res<<"SAT, frameLevel: "<<frameLevel<<std::endl;
        for (int i = 0; i < vec.size(); ++i)
        {
            m_res<<vec[i]<<" ";
        }
        m_res<<std::endl;
    }



}//namespace car