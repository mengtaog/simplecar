#ifndef MAINSOLVER_H
#define MAINSOLVER_H

#include "AigerModel.h"
#include "IMainSolver.h"
#include "minisat/core/Solver.h"

#include <stdio.h>
using namespace Minisat;
namespace car
{

class MainSolver : public IMainSolver, public Minisat::Solver
{
public:
	MainSolver(AigerModel* model);

	void GetUnsatisfiableCore(std::vector<int>& out);

	void GetUnsatisfiableCoreFromBad(std::vector<int>& out) override;

	std::vector<int>* GetAssignment() override;

	bool SolveWithAssumption(std::vector<int>& assumption, int frameLevel);

	void AddClause(std::vector<int>& cube, int frameLevel);

	virtual void AddNewFrame(const std::vector<std::vector<int> >& frame, int frameLevel) override;

	bool SolveWithAssumptionAndBad(std::vector<int>& assumption, int bad);

	bool SolveWithAssumption(std::vector<int>& assignment, int flagId) override;
	
private:
	int GetLiteralId(const Lit &l);

	inline int GetFrameFlag(int frameLevel);

	inline Lit GetLit(int id);



	int m_maxFlag;
	AigerModel* m_model;
	std::vector<int> m_frameFlags;
	vec<Lit> m_assumptions;
	

};

}//namespace car
#endif