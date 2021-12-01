#ifndef OVERSEQUENCE_H
#define OVERSEQUENCE_h

#include <vector>

namespace car
{

class OverSequence
{
public:
	void Insert(std::vector<int> uc, int index);
private:
	int m_frameLevel;


};

}//namespace car



#endif
