#pragma once
#include "yaMonsterState.h"

namespace ya
{
	class Player;
	class PatrolState final : public MonsterState
	{
	public:
		PatrolState(Player* pPlayer);
		virtual ~PatrolState();

		void Tick() override;
		void Enter() override;
		void Exit() override;
	private:

	};

}

