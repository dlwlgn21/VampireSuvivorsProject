#pragma once
#include "Common.h"

namespace ya
{
	class MonsterState;
	class Monster;
	class AI
	{
	public:
		AI();
		~AI();

		void AddMonsterState(MonsterState* pState);

		void Tick();

	private:
		Monster* mpMonster;
		std::unordered_map<eMonsterState, MonsterState*> mStateMap;
		MonsterState* mpCurrMonsterState;


	};

}

