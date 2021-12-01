#ifndef MAINSOLVER_H
#define MAINSOLVER_H

#include "AigerModel.h"
#include "IMainSolver.h"
namespace car
{

class MainSolver : public IMainSolver
{
public:
	MainSolver(AigerModel* model);

	std::vector<int> GetUnsatisfiableCore();

	std::vector<int> GetAssignment();

	bool SolveWithAssumption(std::vector<int>& assumption, int frameLevel);

	void AddClause(std::vector<int>& cube, int frameLevel);

	bool SolveWithAssumptionAndBad(std::vector<int>& assumption, int bad);

private:

	
	
	AigerModel* m_model;
	

};

}//namespace car
#endif