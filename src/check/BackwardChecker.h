#ifndef BACKWARDCHECKER_H
#define BACKWARDCHECKER_H

#include "BaseChecker.h"
#include "../model/State.h"
#include "../model/OverSequence.h"
#include "../model/ISolver.h"

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

	bool ImmediateSatisfiable(int badId);

	OverSequence m_overSequence;
	Settings m_settings;
	AigerModel* m_model;
	State* m_initialState;
	IMainSolver* m_mainSolver;
	ISolver* m_startSolver;
	ISolver* m_invSolver;
};

}//namespace car

#endif