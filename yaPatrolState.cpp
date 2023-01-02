#include "yaPatrolState.h"
#include "yaPlayer.h"

namespace ya
{
	PatrolState::PatrolState(Player* pPlayer)
		: MonsterState(eMonsterState::PATROL, pPlayer)
	{
	}
	PatrolState::~PatrolState()
	{
	}
	void PatrolState::Tick()
	{
	}
	void PatrolState::Enter()
	{
	}
	void PatrolState::Exit()
	{
	}
}