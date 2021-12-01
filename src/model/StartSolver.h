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

		std::vector<int> GetUnsatisfiableCore();

		std::vector<int> GetAssignment();

		bool SolveWithAssumption(std::vector<int>& assumption, int frameLevel);

		void AddClause(std::vector<int>& cube, int frameLevel);

	private:
		AigerModel* m_model;

	};

}//namespace car
#endif