#ifndef STATE_H
#define STATE_H

#include <vector>

namespace car
{

class State
{
public:
	State(State* inPreState, std::vector<int>* inAssignment, int inDepth);
	~State() {delete assignment;}

	int depth;
	State* preState;
	std::vector<int>* assignment;
	
};

}//namespace car

#endif
