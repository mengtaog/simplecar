#ifndef UNDERSEQUENCE_H
#define UNDERSEQUENCE_H

#include "State.h"
#include <vector>
namespace car
{

class UnderSequence
{
public:
    void push(State* state)
    {
        while(m_sequence.size() <= state->depth)
        {
            m_sequence.emplace_back(std::vector<State*>());
        }
        m_sequence[state->depth].push_back(state);
    }

    int size() {return m_sequence.size();}

    std::vector<State*>& operator[] (int i) {return m_sequence[i];}
private:
    std::vector<std::vector<State*> > m_sequence;
};

}//namespace car

#endif