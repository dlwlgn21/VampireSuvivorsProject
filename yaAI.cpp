#include "yaAI.h"
#include "yaMonsterState.h"

namespace ya
{
	AI::AI()
		: mpMonster(nullptr)
		, mpCurrMonsterState(nullptr)
		, mStates{ 0, }
	{
	}
	AI::~AI()
	{
		for (int i = 0; i < static_cast<UINT>(eMonsterState::COUNT); ++i)
		{
			if (mStates[i] != nullptr)
				{ delete mStates[i]; }
		}

	}
	void AI::AddMonsterState(MonsterState* pState)
	{
		eMonsterState eState = pState->GetEMonsterState();
		
		if (mStates[static_cast<UINT>(eState)] == nullptr)
		{
			mStates[static_cast<UINT>(eState)] = pState;
			pState->SetAI(this);
			return;
		}
		assert(false);
		return;
	}
	void AI::Tick()
	{
		//mpCurrMonsterState->Tick();
	}
}