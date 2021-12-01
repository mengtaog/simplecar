#include "BackwardChecker.h"
#include "../model/MainSolver.h"
#include "../model/StartSolver.h"
namespace car
{
	BackwardChecker::BackwardChecker(Settings settings, AigerModel* model) : m_settings(settings), m_model(model)
	{
		m_initialState = new State(model->GetInitialState());
	}


	bool BackwardChecker::Run()
	{
		for (int i = 0, maxI = m_model->GetOutputs().size(); i < maxI; ++i)
		{
			int badId = m_model->GetOutputs().at(i);
			bool result = Check(badId);


		}
		return true;
	}

	bool BackwardChecker::Check(int badId)
	{
		if (m_model->IsTrue(badId))
		{
			//placeholder
			return true;
		}
		else if (m_model->IsFalse(badId))
		{
			//placeholder
			return false;
		}

		Init();

		if (ImmediateSatisfiable(badId))
		{
			return true;
		}

		std::vector<int> uc = m_mainSolver->GetUnsatisfiableCore();

	}


	void BackwardChecker::Init()
	{
		m_overSequence = OverSequence();
		m_mainSolver = new MainSolver(m_model);
		m_startSolver = new StartSolver(m_model);
	}

	bool BackwardChecker::ImmediateSatisfiable(int badId)
	{
		std::vector<int>& init = m_initialState->GetAssignment();
		std::vector<int> assumptions(init.size()+1);
		std::copy(init.begin(), init.end(), assumptions.begin());
		assumptions.emplace_back(badId);
		bool result = dynamic_cast<MainSolver*>(m_mainSolver)->SolveWithAssumptionAndBad(assumptions, badId);
		return result;
	}




}//namespace car