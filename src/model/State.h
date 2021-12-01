#ifndef STATE_H
#define STATE_H

#include <vector>

namespace car
{

class State
{
public:
	State(const std::vector<int>& assignment);

	std::vector<int>& GetAssignment() { return m_assignment; }
private:
	std::vector<int> m_assignment;
};

}//namespace car

#endif
