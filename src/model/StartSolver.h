#ifndef STARTSOLVER_H
#define STARTSOLVER_H

#include "ISolver.h"
#include "AigerModel.h"

namespace car
{

class StartSolver : public ISolver
{
public:
	StartSolver(AigerModel* model);

	void GetUnsatisfiableCore(std::vector<int>& out);

	std::vector<int>* GetAssignment();

	bool SolveWithAssumption(std::vector<int>& assumption, int frameLevel);

	void AddClause(std::vector<int>& cube, int frameLevel);

	void AddNewFrame(const std::vector<std::vector<int> >& frame, int frameLevel);

private:

	inline void Reset();



	AigerModel* m_model;

};

}//namespace car

#endif