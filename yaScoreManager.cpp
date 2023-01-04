#include "yaScoreManager.h"

namespace ya
{

	void ScoreManager::Initialize()
	{
		mPleyerLevel = 1;
		mKillCount = 0;
		mSuvivorTime = 0.0f;
	}

	void ScoreManager::UpdatePlayerLevel(UINT level)
	{
		mPleyerLevel = level;
	}
	void ScoreManager::UpdateKillCount(UINT count)
	{
		mKillCount = count;
	}
	void ScoreManager::UpdateSuvivorTime(float totalTime)
	{
		mSuvivorTime = totalTime;
	}

}