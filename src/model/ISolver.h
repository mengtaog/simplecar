#ifndef ISOLVER_H
#define ISOLVER_H

#include <vector>
#include "State.h"
namespace car
{

class ISolver
{
public:
	virtual void GetUnsatisfiableCore(std::vector<int>& out) = 0;

	virtual std::vector<int>* GetAssignment() = 0;

	virtual bool SolveWithAssumption(std::vector<int>& assumption, int frameLevel) = 0;

	virtual void AddNewFrame(const std::vector<std::vector<int> >& frame, int frameLevel) = 0;

	virtual void AddClause(std::vector<int>& cube, int frameLevel) = 0;
	
private:
};

} //namespace car


#endif
