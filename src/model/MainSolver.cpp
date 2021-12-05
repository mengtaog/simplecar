#include "MainSolver.h"

namespace car
{
	void MainSolver::GetUnsatisfiableCoreFromBad(std::vector<int>& out)
	{
		std::vector<int> uc;
		for (int i = 0; i < conflict.size(); ++i)
		{
			uc.emplace_back(-GetLiteralId(conflict[i]));
		}
		out.swap(uc);
	}

	int MainSolver::GetLiteralId(const Minisat::Lit &l)
	{
		return sign(l) ? -(var(l) + 1) : var(l) + 1;
	}

	void MainSolver::AddNewFrame(const std::vector<std::vector<int> >& frame, int frameLevel)
	{
		/*
		vec<Lit> literals;
		literals.push(GetLit(-GetFrameFlag(frameLevel)));
		for (int i = 0; i < frame.size(); ++i)
		{
			literals.push(GetLit(-frame[i]));
		}
		addClause(literals);
		*/
	}

	bool MainSolver::SolveWithAssumptionAndBad(std::vector<int>& assumption, int badId)
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

	bool MainSolver::SolveWithAssumption(std::vector<int>& assignment, int frameLevel)
	{
		m_assumptions.clear();
		m_assumptions.push(GetLit(GetFrameFlag(frameLevel)));
		for(auto it = assignment.begin(); it != assignment.end(); ++it)
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

	std::vector<int>* MainSolver::GetAssignment()
	{
		assert(m_model->GetNumInputs() < nVars());
		std::vector<int>* result = new std::vector<int>();
		result->reserve(m_model->GetNumInputs() + m_model->GetNumLatches());
		for (int i = 0; i <m_model->GetNumInputs(); ++i)
		{
			if (model[i] == l_True)
			{
				result->emplace_back(i+1);
			}
			else if (model[i] == l_False)
			{
				result->emplace_back(-i-1);
			}
		}
		for (int i = m_model->GetNumInputs(), end = m_model->GetNumInputs() + m_model->GetNumLatches(); i < end; ++i)
		{
			int p = m_model->GetPrime(i+1);
			lbool val = model[abs(p)-1];
			if ((val == l_True && p > 0) || (val == l_False && p < 0))
			{
				result->emplace_back(i+1);
			}
			else
			{
				result->emplace_back(-i-1);
			}
		}
		return result;
	}

#pragma region private
	inline Lit MainSolver::GetLit(int id)
	{
		if (id == 0)
		{
			//placeholder
		}
		int var = abs(id)-1;
		while(var >= nVars()) newVar();
		return ((id > 0)? mkLit(var):~mkLit(var));
	}


	inline int MainSolver::GetFrameFlag(int frameLevel)
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

#pragma endregion

} //namespace car