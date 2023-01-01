#pragma once
#include "yaMonsterState.h"

namespace ya
{
	class PatrolState final : public MonsterState
	{
	public:
		PatrolState();
		virtual ~PatrolState();

		void Tick() override;
		void Enter() override;
		void Exit() override;
	private:

	};

}

