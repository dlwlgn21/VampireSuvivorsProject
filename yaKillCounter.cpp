#include "yaKillCounter.h"


namespace ya
{
	void KillCounter::InitializeKillCount()
	{
		mKillCount = 0;
	}
	void KillCounter::IncreaseKillCount()
	{
		++mKillCount;
	}
}