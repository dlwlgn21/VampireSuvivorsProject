#pragma once
#include "Common.h"

namespace ya
{
	class KillCounter final
	{
	public:
		static KillCounter& GetInstance()
		{
			static KillCounter instance;
			return instance;
		}

		KillCounter(const KillCounter& other) = delete;
		KillCounter& operator=(const KillCounter& other) = delete;

		void InitializeKillCount();
		void IncreaseKillCount();
		__forceinline UINT GetKillCount() const { return mKillCount; }

	private:
		KillCounter(): mKillCount(0) {}
		~KillCounter() = default;
	private:
		UINT mKillCount;
	};
}

