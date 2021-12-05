#ifndef OVERSEQUENCE_H
#define OVERSEQUENCE_h

#include <vector>

namespace car
{

class OverSequence
{
public:
	void Insert(const std::vector<int>& uc, int index);
	void GetFrame(int frameLevel, std::vector<std::vector<int> >& out);
	bool IsImplyFrame(std::vector<int>& state, int frameLevel);
	int GetLength();
private:
	int m_frameLevel;


};

}//namespace car



#endif
