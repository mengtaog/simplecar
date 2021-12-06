#ifndef CARSOLVER_H
#define CARSOLVER_H

#include "ISolver.h"
#include "minisat/core/Solver.h"
#include "AigerModel.h"

using namespace Minisat;

namespace car
{

class CarSolver: public ISolver, public Minisat::Solver
{
public:
	CarSolver(AigerModel* model);
	~CarSolver();
    void GetUnsatisfiableCoreFromBad(std::vector<int>& out);
	void AddClause(const std::vector<int>& clause);
	void AddClause(const std::vector<int>& clause, int frameLevel);
	void GetUnsatisfiableCore(std::vector<int>& out);
	void AddNewFrame(const std::vector<std::vector<int> >& frame, int frameLevel);
	bool SolveWithAssumptionAndBad(std::vector<int>& assumption, int badId);
	bool SolveWithAssumption();
	inline void AddAssumption(int id) {m_assumptions.push(GetLit(id));}
	bool SolveWithAssumption(std::vector<int>& assumption, int frameLevel);
	std::vector<int>* GetAssignment();

	inline void AddConstraintOr(const std::vector<std::vector<int> > frame);
	inline void AddConstraintAnd(const std::vector<std::vector<int> > frame);

	
	inline void FlipLastConstrain();
private:

    inline int GetLiteralId(const Lit &l);
	inline int GetFrameFlag(int frameLevel);
	inline Lit GetLit(int id);
	inline int GetNewVar() {return ++m_maxFlag;}
    
    int m_maxFlag;
	AigerModel* m_model;
	std::vector<int> m_frameFlags;
	vec<Lit> m_assumptions;
};

}//namespace car

#endif