#pragma once
#include "yaMonsterState.h"

namespace ya
{
	class Player;
	class TraceState final : public MonsterState
	{
	public:
		TraceState(Player* pPlayer);
		virtual ~TraceState();

		void Tick() override;
		void Enter() override;
		void Exit() override;
	private:

	};

}

