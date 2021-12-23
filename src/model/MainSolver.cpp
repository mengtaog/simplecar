#include "MainSolver.h"

namespace car
{
    MainSolver::MainSolver(AigerModel* model)
    {
        m_model = model;
        m_maxFlag = model->GetMaxId()+1;
		auto& clause = m_model->GetClause();
		for (int i = 0; i < clause.size(); ++i)
		{
			AddClause(clause[i]);
		}
    }

}//namespace car