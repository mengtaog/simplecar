#include "CarSolver.h"
#include <algorithm>
using namespace Minisat;

namespace  car
{
	CarSolver::CarSolver() {}

	CarSolver::~CarSolver()
	{
		;
	}

	bool CarSolver::SolveWithAssumption()
	{
		lbool result = solveLimited(m_assumptions);
		if (result == l_True)
		{
			return true;
		}
		else if(result == l_False)
		{
			return false;
		}
		else // result == l_Undef
		{
			//placeholder
		}
	}

    bool CarSolver::SolveWithAssumption(std::vector<int>& assumption, int frameLevel)
    {
		m_assumptions.clear();
		m_assumptions.push(GetLit(GetFrameFlag(frameLevel)));
		for(auto it = assumption.begin(); it != assumption.end(); ++it)
		{
			m_assumptions.push(GetLit(*it));
		}
		lbool result = solveLimited(m_assumptions);
		if (result == l_True)
		{
			return true;
		}
		else if(result == l_False)
		{
			return false;
		}
		else // result == l_Undef
		{
			//placeholder
		}
    }

	void CarSolver::AddClause(const std::vector<int>& clause)
    {
        vec<Lit> literals;
        for (int i = 0; i < clause.size(); ++i)
        {
            literals.push(GetLit(clause[i]));
        }
        bool result = addClause(literals);
        assert (result != false);
    }

	void CarSolver::AddUnsatisfiableCore(const std::vector<int>& clause, int frameLevel)
	{
		int flag = GetFrameFlag(frameLevel);
		vec<Lit> literals;
		literals.push(GetLit(-flag));
		for (int i = 0; i < clause.size(); ++i)
        {
            literals.push(GetLit(-m_model->GetPrime(clause[i])));
        }
        bool result = addClause(literals);
        if (!result)
        {
            //placeholder
        }
	}

    std::pair<std::vector<int>*, std::vector<int>* > CarSolver::GetAssignment()
	{
		assert(m_model->GetNumInputs() < nVars());
		std::vector<int>* inputs = new std::vector<int>();
		std::vector<int>* latches = new std::vector<int>();
		inputs->reserve(m_model->GetNumInputs());
		latches->reserve(m_model->GetNumLatches());
		for (int i = 0; i <m_model->GetNumInputs(); ++i)
		{
			if (model[i] == l_True)
			{
				inputs->emplace_back(i+1);
			}
			else if (model[i] == l_False)
			{
				inputs->emplace_back(-i-1);
			}
		}
		for (int i = m_model->GetNumInputs(), end = m_model->GetNumInputs() + m_model->GetNumLatches(); i < end; ++i)
		{
			int p = m_model->GetPrime(i+1);
			lbool val = model[abs(p)-1];
			if ((val == l_True && p > 0) || (val == l_False && p < 0))
			{
				latches->emplace_back(i+1);
			}
			else
			{
				latches->emplace_back(-i-1);
			}
		}
		return std::pair<std::vector<int>*, std::vector<int>* >(inputs, latches);
	}

    void CarSolver:: GetUnsatisfiableCoreFromBad(std::vector<int>& out, int badId)
	{
		std::vector<int> uc;
		int val;
		for (int i = 0; i < conflict.size(); ++i)
		{
			val = -GetLiteralId(conflict[i]);
			if (m_model->IsLatch(val))
			{
				uc.emplace_back(val);
			}
		}
		std::sort(uc.begin(), uc.end(), cmp);
		out.swap(uc);
	}

	void CarSolver::GetUnsatisfiableCore(std::vector<int>& out)
	{
		std::vector<int> uc;
		int val;
		for (int i = 0; i < conflict.size(); ++i)
		{
			val = -GetLiteralId(conflict[i]);
			if (m_model->IsLatch(val))
			{
				uc.emplace_back(val);
			}
		}
		std::sort(uc.begin(), uc.end(), cmp);
		out.swap(uc);
	}

	void CarSolver::AddNewFrame(const std::vector<std::vector<int> >& frame, int frameLevel)
	{
		for (int i = 0; i < frame.size(); ++i)
		{
			AddUnsatisfiableCore(frame[i], frameLevel);
		}
	}

    bool CarSolver::SolveWithAssumptionAndBad(std::vector<int>& assumption, int badId)
	{
		m_assumptions.clear();
		m_assumptions.push(GetLit(badId));
		for(auto it = assumption.begin(); it != assumption.end(); ++it)
		{
			m_assumptions.push(GetLit(*it));
		}
		lbool result = solveLimited(m_assumptions);
		if (result == l_True)
		{
			return true;
		}
		else if(result == l_False)
		{
			return false;
		}
		else // result == l_Undef
		{
			//placeholder
		}
	}

	inline void CarSolver::AddConstraintOr(const std::vector<std::vector<int> > frame)
	{
		std::vector<int> clause;
		for (int i = 0; i < frame.size(); ++i)
		{
			int flag = GetNewVar();
			clause.push_back(flag);
			for (int j = 0; j < frame[i].size(); ++j)
			{
				AddClause(std::vector<int> {-flag, frame[i][j]});
			}
		}
		AddClause(clause);
	}

	inline void CarSolver::AddConstraintAnd(const std::vector<std::vector<int> > frame)
	{
		int flag = GetNewVar();
		for (int i = 0; i < frame.size(); ++i)
		{
			std::vector<int> clause;
			for (int j = 0; j < frame[i].size(); ++j)
			{
				clause.push_back(-frame[i][j]);
			}
			clause.push_back(-flag);
			AddClause(clause);
		}
		AddAssumption(flag);
	}

	inline void CarSolver::FlipLastConstrain()
	{
		Lit lit = m_assumptions.last();
		m_assumptions.pop();
		m_assumptions.push(~lit);
	}

#pragma region private
	inline Lit CarSolver::GetLit(int id)
	{
		if (id == 0)
		{
			//placeholder
		}
		int var = abs(id)-1;
		while(var >= nVars()) newVar();
		return ((id > 0)? mkLit(var):~mkLit(var));
	}


	inline int CarSolver::GetFrameFlag(int frameLevel)
	{
		if (frameLevel < 0)
		{
			//placeholder
		}
		while (m_frameFlags.size() <= frameLevel)
		{
			m_frameFlags.emplace_back(m_maxFlag++);
		}
		return m_frameFlags[frameLevel];
	}

    inline int CarSolver::GetLiteralId(const Minisat::Lit &l)
	{
		return sign(l) ? -(var(l) + 1) : var(l) + 1;
	}

	

#pragma endregion


}//namespace car