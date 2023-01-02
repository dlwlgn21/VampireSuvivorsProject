#include "yaMonsterState.h"
#include "yaPlayer.h"

namespace ya
{
	MonsterState::MonsterState(eMonsterState eState, Player* pPlayer)
		: meState(eState)
		, mpPlayer(pPlayer)
		, mpAI(nullptr)
	{
		assert(mpPlayer != nullptr);
	}
	MonsterState::~MonsterState()
	{
	}
}