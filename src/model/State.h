#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
#include <stdlib.h>

namespace car
{

class State
{
public:
	State(State* inPreState, std::vector<int>* inInputs, std::vector<int>* inLatches, int inDepth):
		preState(inPreState), inputs(inInputs), latches(inLatches), depth(inDepth)
	{
		
	}
	~State() 
	{
		delete inputs;
		delete latches;
	}

	std::string GetValueOfLatches()
	{
		std::string result = "";
		result.reserve(numLatches);
		int j = 0;
		for (int i = 0; i < State::numLatches; ++i)
		{
			if (State::numInputs + i + 1 < abs((*latches)[j]))
			{
				result += "x";
			}
			else
			{
				result += (latches->at(j) > 0) ? "1" : "0";
				++j;
			}
		}
		return result;
	}

	std::string GetValueOfInputs()
	{
		std::string result = "";
		result.reserve(numInputs);
		for (int i = 0; i < numInputs; ++i)
		{
			result += (inputs->at(i) > 0) ? "1" : "0";
		}
		return result;
		
	}
	static int numInputs;
	static int numLatches;
	int depth;
	State* preState;
	std::vector<int>* inputs;
	std::vector<int>* latches;
	
};


}//namespace car

#endif
