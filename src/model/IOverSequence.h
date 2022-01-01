#ifndef IOVERSEQUENCE_H
#define IOVERSEQUENCE_H

#include <vector>

namespace car
{

class IOverSequence
{
public:
    virtual void Insert(std::vector<int>& uc, int index) = 0;
	
	virtual void GetFrame(int frameLevel, std::vector<std::vector<int> >& out) = 0;
	
    virtual bool IsBlockedByFrame(std::vector<int>& state, int frameLevel) = 0;
	
	virtual int GetLength() = 0;

	virtual std::vector<std::vector<int> >& operator[] (int i) = 0;

	int effectiveLevel;
};

}//namespace car
#endif