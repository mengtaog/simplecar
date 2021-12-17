#ifndef OVERSEQUENCE_H
#define OVERSEQUENCE_h

#include <vector>
#include <cmath>

namespace car
{

class OverSequence
{
public:
	OverSequence() {}
	OverSequence(int inputNums): m_numInputs(inputNums)
	{

	}

	void Insert(const std::vector<int>& uc, int index)
	{
		if (index >= m_sequence.size())
		{
			m_sequence.emplace_back(std::vector<std::vector<int> >());
		}
		m_sequence[index].push_back(uc);
	}
	void GetFrame(int frameLevel, std::vector<std::vector<int> >& out)
	{
		if (frameLevel >= m_sequence.size()) return;
		out = m_sequence[frameLevel];
	}
	bool IsImplyFrame(std::vector<int>& state, int frameLevel)
	{
		for (int i = 0; i < m_sequence[frameLevel].size(); ++i)
		{
			for (int j = 0; j < m_sequence[frameLevel][i].size(); ++j)
			{
				int index = abs(m_sequence[frameLevel][i][j]) - m_numInputs - 1;
				if (state[index] != m_sequence[frameLevel][i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
	int GetLength()
	{
		return m_sequence.size();
	}

	int effectiveLevel;
private:
	int m_numInputs;
	std::vector<std::vector<std::vector<int> > > m_sequence;


};

}//namespace car



#endif
