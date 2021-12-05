#ifndef IMAINSOLVER_H
#define IMAINSOLVER_H
#include "ISolver.h"
namespace car
{

class IMainSolver : public ISolver
{
public:
	virtual bool SolveWithAssumptionAndBad(std::vector<int>& assumption, int badId) = 0;

	virtual bool SolveWithAssumption(std::vector<int>& assignment, int frameLevel) = 0;

	virtual void GetUnsatisfiableCoreFromBad(std::vector<int>& out) = 0;
};


}//namespace car



#endif
