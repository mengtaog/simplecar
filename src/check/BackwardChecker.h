#ifndef BACKWARDCHECKER_H
#define BACKWARDCHECKER_H

#include "BaseChecker.h"
#include "../model/State.h"
#include "../model/OverSequence.h"
#include "UnderSequence.h"
#include "../model/ISolver.h"
#include "Task.h"

namespace car
{

class BackwardChecker : public BaseChecker
{
public:
	BackwardChecker(Settings settings, AigerModel* model);
	bool Run();
	bool Check(int badId);
private:
	void Init();

	void AddUnsatisfiableCore(std::vector<int>& uc, int frameLevel);

	bool ImmediateSatisfiable(int badId);

	bool isInvExisted();

	bool IsInvariant(int frameLevel);

	int GetNewLevel(State* state, int start = 0);



	int m_minUpdateLevel;
	OverSequence m_overSequence;
	UnderSequence m_underSequence;
	Settings m_settings;
	AigerModel* m_model;
	State* m_initialState;
	ISolver* m_mainSolver;
	ISolver* m_invSolver;
};

}//namespace car

#endif