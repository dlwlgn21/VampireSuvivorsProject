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
		// CPU ���� ������ ( 1�ʴ� �� �� )
		static LARGE_INTEGER mCPUFrequency;		// CPU ������
		static LARGE_INTEGER mPrevFrequency;		// �� ���� ������ ������
		static LARGE_INTEGER mCurFrequency;		// �� ���� ������ ������
		static HWND mHwnd;
		static float mDeltaTime;
		static float mTime;
	};
}

