#include "BackwardChecker.h"
#include "../model/MainSolver.h"
#include "../model/StartSolver.h"
#include <stack>
namespace car
{
	BackwardChecker::BackwardChecker(Settings settings, AigerModel* model) : m_settings(settings), m_model(model)
	{
		std::vector<int>* init = new std::vector<int>(model->GetInitialState());
		m_initialState = new State (nullptr, init, 0);
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
		#pragma region early stage
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

		std::vector<int> uc;
		m_mainSolver->GetUnsatisfiableCoreFromBad(uc);
		if (uc.empty()) //uc is empty when Bad by itself is unsatisfying
		{
			//placeholder
			return true;
		}
		m_overSequence.Insert(uc, 0);
		{
			std::vector<std::vector<int> > frame;
			m_overSequence.GetFrame(0, frame);
			m_mainSolver->AddNewFrame(frame, 0);
		}
		# pragma endregion 

		//main stage
		int frameStep = 0;
		while (true)
		{
			std::stack<Task> workingStack;
			for(int i = m_underSequence.size() - 1; i >= 0; --i)
			{
				for (int j = 0; j < m_underSequence[i].size(); ++j)
				{
					workingStack.emplace(&m_underSequence[i][j], frameStep, false);
				}
			}
			while (!workingStack.empty())
			{
				Task& task = workingStack.top();
				
				if (!task.isLocated)
				{
					task.frameLevel = GetNewLevel(task.state, task.frameLevel+1);
					if (task.frameLevel == m_overSequence.GetLength())
					{
						workingStack.pop();
						continue;
					}
				}
				task.isLocated = false;

				if (task.frameLevel == -1)
				{
					bool result = m_mainSolver->SolveWithAssumptionAndBad(*(task.state->assignment), badId);
					if (result)
					{
						//placeholder, get counterexample
					}
					else
					{
						std::vector<int> uc;
						m_mainSolver->GetUnsatisfiableCoreFromBad(uc);
						if (uc.empty())
						{
							//placeholder, uc is empty => safe
						}
						m_mainSolver->AddClause(uc, task.frameLevel+1);
						m_overSequence.Insert(uc, task.frameLevel+1);
						task.frameLevel++;
						continue;
					}
				}

				bool result = m_mainSolver->SolveWithAssumption(*(task.state->assignment), task.frameLevel);
				if (result)
				{
					//Solver return SAT, get a new State, then continue
					State* newState = new State(task.state, m_mainSolver->GetAssignment(), task.state->depth+1);
					m_underSequence.push(newState);
					int newFrameLevel = GetNewLevel(newState);
					workingStack.emplace(newState, newFrameLevel, true);
					continue;
				}
				else
				{
					//Solver return UNSAT, get uc, then continue
					std::vector<int> uc;
					m_mainSolver->GetUnsatisfiableCore(uc);
					if (uc.empty())
					{
						//placeholder, uc is empty => safe
					}
					m_mainSolver->AddClause(uc, task.frameLevel+1);
					m_overSequence.Insert(uc, task.frameLevel+1);
					task.frameLevel++;
					continue;
				}
			}
			std::vector<std::vector<int> > lastFrame;
			frameStep++;
			m_overSequence.GetFrame(frameStep, lastFrame);
			m_mainSolver->AddNewFrame(lastFrame, frameStep);
			if (isInvExisted())
			{
				//placeholder
			}
		}
	}
		


	void BackwardChecker::Init()
	{
		m_overSequence = OverSequence();
		m_mainSolver = new MainSolver(m_model);
		m_startSolver = new StartSolver(m_model);
	}

	bool BackwardChecker::ImmediateSatisfiable(int badId)
	{
		std::vector<int>& init = *(m_initialState->assignment);
		std::vector<int> assumptions(init.size()+1);
		std::copy(init.begin(), init.end(), assumptions.begin());
		assumptions.emplace_back(badId);
		bool result = m_mainSolver->SolveWithAssumptionAndBad(assumptions, badId);
		return result;
	}

	bool BackwardChecker::isInvExisted()
	{
		//placeholder
	}

	int BackwardChecker::GetNewLevel(State* state, int start = 0)
	{
		for (int i = start; i < m_overSequence.GetLength(); ++i)
		{
			if (!m_overSequence.IsImplyFrame(*(state->assignment), i))
			{
				return i-1;
			}
		}
		return m_overSequence.GetLength(); //placeholder
	}




}//namespace car