#pragma once
#include "Common.h"

namespace ya
{
	class MonsterState;
	class Monster;
	class AI
	{
	public:
		friend class Monster;
		AI();
		~AI();

		void AddMonsterState(MonsterState* pState);
		__forceinline void SetAIToMonster(Monster* pMonster) { assert(pMonster != nullptr); mpMonster = pMonster; };
		void Tick();

	private:
		Monster* mpMonster;
		MonsterState* mStates[static_cast<UINT>(eMonsterState::COUNT)];
		MonsterState* mpCurrMonsterState;
		
	};

}

