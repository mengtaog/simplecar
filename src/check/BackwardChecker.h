#ifndef BACKWARDCHECKER_H
#define BACKWARDCHECKER_H

#include "BaseChecker.h"
#include "State.h"
#include "OverSequence.h"
#include "UnderSequence.h"
#include "ISolver.h"
#include "Task.h"
#include "Log.h"
#include <assert.h>
namespace car
{

class BackwardChecker : public BaseChecker
{
public:
	BackwardChecker(Settings settings, AigerModel* model);
	~BackwardChecker();
	bool Run();
	bool Check(int badId);
private:
	void Init();

	void AddUnsatisfiableCore(std::vector<int>& uc, int frameLevel);

	bool ImmediateSatisfiable(int badId);

	bool isInvExisted();

	bool IsInvariant(int frameLevel);

	int GetNewLevel(State* state, int start = 0);

	string GetFileName(string filePath)
	{
		auto startIndex = filePath.find_last_of("/");
		if (startIndex == string::npos)
		{
			startIndex = 0;
		}
		else
		{
			startIndex++;
		}
		auto endIndex = filePath.find_last_of(".");
		assert (endIndex != string::npos);
		return filePath.substr(startIndex, endIndex-startIndex);	
	}



	int m_minUpdateLevel;
	OverSequence m_overSequence;
	UnderSequence m_underSequence;
	Settings m_settings;
	Log* m_log;
	AigerModel* m_model;
	State* m_initialState;
	ISolver* m_mainSolver;
	ISolver* m_invSolver;
};

}//namespace car

#endif