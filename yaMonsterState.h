#pragma once
#include "Common.h"

namespace ya
{
	class Player;
	class AI;
	class MonsterState
	{
	public:
		friend class AI;
		MonsterState(eMonsterState eState, Player* pPlayer);
		virtual ~MonsterState();
		
		__forceinline void SetAI(AI* pAI) { assert(pAI != nullptr); mpAI = pAI; }
		__forceinline AI* GetAI() const { return mpAI; }
		__forceinline eMonsterState GetEMonsterState() const { return meState; }

		virtual void Tick() = 0;
		virtual void Enter() = 0;
		virtual void Exit() = 0;

	protected:
		AI* mpAI;
		Player* mpPlayer;
		eMonsterState meState;
	};

}

