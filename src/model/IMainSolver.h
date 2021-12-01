#ifndef IMAINSOLVER_H
#define IMAINSOLVER_H
#include "ISolver.h"
namespace car
{

class IMainSolver : public ISolver
{
public:
	virtual bool SolveWithAssumptionAndBad(std::vector<int>& assumption, int bad) = 0;
};


}//namespace car



#endif
