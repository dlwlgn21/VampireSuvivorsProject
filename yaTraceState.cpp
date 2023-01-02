#include "yaTraceState.h"
#include "yaPlayer.h"

namespace ya
{
	TraceState::TraceState(Player* pPlayer)
		: MonsterState(eMonsterState::TRACE, pPlayer)
	{
	}
	TraceState::~TraceState()
	{
	}
	void TraceState::Tick()
	{
	}
	void TraceState::Enter()
	{
	}
	void TraceState::Exit()
	{
	}
}