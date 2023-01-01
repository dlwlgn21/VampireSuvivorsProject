#pragma once
#include "Common.h"

namespace ya
{
	class AI;
	class MonsterState
	{
	public:
		friend class AI;
		MonsterState(eMonsterState eState);
		virtual ~MonsterState();
		
		AI* GetAI() const { return mpAI; }
		eMonsterState GetMonsterState() const { return meState; }

		virtual void Tick() = 0;
		virtual void Enter() = 0;
		virtual void Exit() = 0;

	protected:
		AI* mpAI;
		eMonsterState meState;
	};

}

