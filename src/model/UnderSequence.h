#ifndef UNDERSEQUENCE_H
#define UNDERSEQUENCE_H

#include "State.h"
#include <vector>
namespace car
{

class UnderSequence
{
public:
    void push(State* state);

    int size() {return m_sequence.size();}

    std::vector<State*>& operator[] (int i) {return m_sequence[i];}
private:
    std::vector<std::vector<State*> > m_sequence;

};

}//namespace car

#endif