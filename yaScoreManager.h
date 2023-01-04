#pragma once
#include "Common.h"

namespace ya
{
	class ScoreManager final
	{
	public:
		static ScoreManager& GetInstance()
		{
			static ScoreManager instance;
			return instance;
		}
		ScoreManager(const ScoreManager& other) = delete;
		ScoreManager& operator=(const ScoreManager& other) = delete;

		void Initialize();
		void UpdatePlayerLevel(UINT level);
		void UpdateKillCount(UINT count);
		void UpdateSuvivorTime(float totalTime);

		__forceinline UINT GetPlayerLevel() const { return mPleyerLevel; }
		__forceinline UINT GetKillCount() const { return mKillCount; }
		__forceinline float GetSuvivorTime() const { return mSuvivorTime; }

	private:
		ScoreManager()
			: mPleyerLevel(1)
			, mKillCount(0)
			, mSuvivorTime(0.0f)
		{}
		~ScoreManager() = default;

	private:
		UINT mPleyerLevel;
		UINT mKillCount;
		float mSuvivorTime;
	};

}