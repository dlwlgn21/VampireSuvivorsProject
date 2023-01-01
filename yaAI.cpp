#include "yaAI.h"
#include "yaMonsterState.h"

namespace ya
{
	AI::AI()
		: mpMonster(nullptr)
		, mpCurrMonsterState(nullptr)
		, mStateMap()
	{
	}
	AI::~AI()
	{
		for (auto iter = mStateMap.begin(); iter != mStateMap.end(); ++iter)
		{
			if (iter->second != nullptr)
				{ delete iter->second; }
		}
	}
	void AI::AddMonsterState(MonsterState* pState)
	{
	}
	void AI::Tick()
	{
		mpCurrMonsterState->Tick();
	}
}