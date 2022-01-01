#ifndef CARSOLVER_H
#define CARSOLVER_H

#include "ISolver.h"
#include "Solver.h"
#include "AigerModel.h"

using namespace Minisat;

namespace car
{

class CarSolver: public ISolver, public Minisat::Solver
{
public:
	CarSolver();
	~CarSolver();
    void GetUnsatisfiableCoreFromBad(std::vector<int>& out, int badId) override;
	void AddClause(const std::vector<int>& clause) override;
	void AddUnsatisfiableCore(const std::vector<int>& clause, int frameLevel) override;
	void GetUnsatisfiableCore(std::vector<int>& out) override;
	void AddNewFrame(const std::vector<std::vector<int> >& frame, int frameLevel) override;
	bool SolveWithAssumptionAndBad(std::vector<int>& assumption, int badId) override;
	bool SolveWithAssumption() override;
	inline void AddAssumption(int id) override {m_assumptions.push(GetLit(id));}
	bool SolveWithAssumption(std::vector<int>& assumption, int frameLevel) override;
#ifdef __DEBUG__
	std::pair<std::vector<int>*, std::vector<int>* > GetAssignment(std::ofstream& out) override;
#else
	std::pair<std::shared_ptr<std::vector<int> >, std::shared_ptr<std::vector<int> > > GetAssignment() override;
#endif
	inline void AddConstraintOr(const std::vector<std::vector<int> > frame);
	inline void AddConstraintAnd(const std::vector<std::vector<int> > frame);
	inline void FlipLastConstrain();
protected:
	static bool cmp(int a, int b)
	{
		return abs(a) < abs(b);
	}
    inline int GetLiteralId(const Lit &l);
	inline int GetFrameFlag(int frameLevel);
	inline Lit GetLit(int id);
	inline int GetNewVar() {return m_maxFlag++;}

    
    int m_maxFlag;
	std::shared_ptr<AigerModel> m_model;
	std::vector<int> m_frameFlags;
	vec<Lit> m_assumptions;
};

}//namespace car

#endif