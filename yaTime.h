#pragma once
#include "Common.h"

namespace ya
{
	class Time
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		inline static float DeltaTime() { return mDeltaTime; }

	private:
		// CPU 고유 진동수 ( 1초당 몇 번 )
		static LARGE_INTEGER mCPUFrequency;		// CPU 진동수
		static LARGE_INTEGER mPrevFrequency;		// 내 이전 프레임 진동수
		static LARGE_INTEGER mCurFrequency;		// 내 현재 프레임 진동수
		static HWND mHwnd;
		static float mDeltaTime;
		static float mTime;
	};
}

