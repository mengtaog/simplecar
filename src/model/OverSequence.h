#ifndef OVERSEQUENCE_H
#define OVERSEQUENCE_H

#include <vector>
#include <cmath>
#include "IOverSequence.h"
namespace car
{

class OverSequence : public IOverSequence
{
public:
	OverSequence() {}
	OverSequence(int inputNums): m_numInputs(inputNums)
	{

	}

	void Insert(std::vector<int>& uc, int index) override;
	
	void GetFrame(int frameLevel, std::vector<std::vector<int> >& out) override;
	
	bool IsBlockedByFrame(std::vector<int>& state, int frameLevel) override;
	
	int GetLength() override;

private:
	bool IsImply ( std::vector<int>& v1,  std::vector<int>& v2);

	bool comp (int i, int j)
	{
		return abs (i) < abs(j);
	}
	
	int m_numInputs;
	std::vector<std::vector<std::vector<int> > > m_sequence;//frameLevel //uc //literal m_sequence[0][2]
	//for()

};

}//namespace car



#endif
