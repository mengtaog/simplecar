#include "BackwardChecker.h"
#include <stack>
#include <string>
namespace car
{
	BackwardChecker::BackwardChecker(Settings settings, AigerModel* model) : m_settings(settings), m_model(model)
	{
		State::numInputs = model->GetNumInputs();
		State::numLatches = model->GetNumLatches(); 
		m_log = new Log(settings.outputDir + GetFileName(settings.aigFilePath), settings.timelimit/model->GetNumOutputs());
		const std::vector<int>& init = model->GetInitialState();
		std::vector<int>* inputs = new std::vector<int>(State::numInputs, 0);
		std::vector<int>* latches = new std::vector<int>();
		latches->reserve(State::numLatches);
		
		for (int i = 0; i < State::numLatches; ++i)
		{
			latches->push_back(init[i]);
		}
		m_initialState = new State (nullptr, inputs, latches, 0);
	}

	BackwardChecker::~BackwardChecker()
	{
		//delete m_initialState;
		delete m_mainSolver;
		delete m_invSolver;
		delete m_log;
		delete m_model;
	}


	bool BackwardChecker::Run()
	{
		for (int i = 0, maxI = m_model->GetOutputs().size(); i < maxI; ++i)
		{
			int badId = m_model->GetOutputs().at(i);
			bool result = Check(badId);
			//PrintUC();
			if (result)
			{
				m_log->PrintSafe(i);
			}
			else //unsafe
			{
				m_log->PrintCounterExample(i);
			}
			m_log->PrintStatistics();
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
		m_log->Tick();
		m_mainSolver->GetUnsatisfiableCoreFromBad(uc, badId);
		m_log->StatMainSolver();
		if (uc.empty()) //uc is empty when Bad by itself is unsatisfying
		{
			//placeholder
			return true;
		}
		m_overSequence.Insert(uc, 0);
		std::vector<std::vector<int> > frame;
		m_overSequence.GetFrame(0, frame);
		m_mainSolver->AddNewFrame(frame, 0);
		m_overSequence.effectiveLevel = 0;
		
# pragma endregion 

		//main stage
		int frameStep = 0;
		std::stack<Task> workingStack;
		while (true)
		{
			m_minUpdateLevel = m_overSequence.GetLength();
			if (m_settings.end)
			{
				for (int i = 0; i < m_underSequence.size(); ++i)
				{
					for (int j = m_underSequence[i].size()-1; j>=0; --j)
					{
						workingStack.emplace(m_underSequence[i][j], frameStep, false);
					}
				}
			}
			else
			{
				workingStack.emplace(m_underSequence[0][0], frameStep, false);
			}
			
			while (!workingStack.empty())
			{
				if (m_settings.timelimit > 0 && m_log->IsTimeout())
				{
					m_log->Timeout();
				}

				Task& task = workingStack.top();
				
				if (!task.isLocated)
				{
					m_log->Tick();
					task.frameLevel = GetNewLevel(task.state, task.frameLevel+1);
					m_log->StatGetNewLevel();
					if (task.frameLevel > m_overSequence.effectiveLevel)
					{
						workingStack.pop();
						continue;
					}
				}
				task.isLocated = false;

				if (task.frameLevel == -1)
				{
					m_log->Tick();
					bool result = m_mainSolver->SolveWithAssumptionAndBad(*(task.state->latches), badId);
					m_log->StatMainSolver();
					if (result)
					{
						//placeholder, get counterexample
						auto pair = m_mainSolver->GetAssignment();
						State* newState = new State (task.state, pair.first, pair.second, task.state->depth+1);
						m_log->lastState = newState;
						return false;
					}
					else
					{
						std::vector<int> uc;
						m_mainSolver->GetUnsatisfiableCoreFromBad(uc, badId);
						if (uc.empty())
						{
							//placeholder, uc is empty => safe
						}
						m_log->Tick();
						AddUnsatisfiableCore(uc, task.frameLevel+1);
						m_log->StatUpdateUc();
						task.frameLevel++;
						continue;
					}
				}
				m_log->Tick();
				bool result = m_mainSolver->SolveWithAssumption(*(task.state->latches), task.frameLevel);
				m_log->StatMainSolver();
				if (result)
				{
					//Solver return SAT, get a new State, then continue
					auto pair = m_mainSolver->GetAssignment();
					State* newState = new State (task.state, pair.first, pair.second, task.state->depth+1);
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
					m_log->Tick();
					AddUnsatisfiableCore(uc, task.frameLevel+1);
					m_log->StatUpdateUc();
					task.frameLevel++;
					continue;
				}
			}
			std::vector<std::vector<int> > lastFrame;
			frameStep++;
			m_overSequence.GetFrame(frameStep, lastFrame);
			m_mainSolver->AddNewFrame(lastFrame, frameStep);
			m_overSequence.effectiveLevel++;
			
			m_log->Tick();
			if (isInvExisted())
			{
				m_log->StatInvSolver();
				return true;
			}
			m_log->StatInvSolver();
		}
	}
		


	void BackwardChecker::Init()
	{
		m_overSequence = OverSequence(m_model->GetNumInputs());
		m_underSequence = UnderSequence();
		m_underSequence.push(m_initialState);
		m_mainSolver = new MainSolver(m_model);
		m_invSolver = new InvSolver(m_model);
		m_log->ResetClock();
	}

	void BackwardChecker::AddUnsatisfiableCore(std::vector<int>& uc, int frameLevel)
	{
		if (frameLevel <= m_overSequence.effectiveLevel)
		{
			m_mainSolver->AddUnsatisfiableCore(uc, frameLevel);
		}
		m_overSequence.Insert(uc, frameLevel);
		if(frameLevel < m_minUpdateLevel)
		{
			m_minUpdateLevel = frameLevel;
		}
	}

	bool BackwardChecker::ImmediateSatisfiable(int badId)
	{
		std::vector<int>& init = *(m_initialState->latches);
		std::vector<int> assumptions;
		assumptions.resize((init.size()));
		std::copy(init.begin(), init.end(), assumptions.begin());
		//assumptions[assumptions.size()-1] = badId;
		bool result = m_mainSolver->SolveWithAssumptionAndBad(assumptions, badId);
		return result;
	}

	bool BackwardChecker::isInvExisted()
	{
		if (m_invSolver == nullptr)
		{
			m_invSolver = new InvSolver(m_model);
		}
		bool result = false;
		for (int i = 0; i < m_overSequence.GetLength(); ++i)
		{
			if (IsInvariant(i))
			{
				result = true;
			}
		}
		delete m_invSolver;
		m_invSolver = nullptr;
		return result;
	}

	int BackwardChecker::GetNewLevel(State* state, int start = 0)
	{
		for (int i = start; i < m_overSequence.GetLength(); ++i)
		{
			if (!m_overSequence.IsBlockedByFrame(*(state->latches), i))
			{
				return i-1;
			}
		}
		return m_overSequence.GetLength()-1; //placeholder
	}

	bool BackwardChecker::IsInvariant(int frameLevel)
	{
		std::vector<std::vector<int> > frame;
		m_overSequence.GetFrame(frameLevel, frame);

		if (frameLevel < m_minUpdateLevel)
		{
			m_invSolver->AddConstraintOr(frame);
			return false;
		}

		m_invSolver->AddConstraintAnd(frame);
 		bool result = !m_invSolver->SolveWithAssumption();
		m_invSolver->FlipLastConstrain();
		m_invSolver->AddConstraintOr(frame);
		return result;
	}

	std::string PrintState(std::vector<int>& vec)
	{
		string res = "";
		for (int i = 0; i < vec.size(); ++i)
		{
			res += std::to_string(vec[i]);
		}
		return res;
	}


}//namespace car