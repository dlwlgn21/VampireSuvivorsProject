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

		static void Stop();
		static void Resume();
		static float TotalTime();
		static void SetScale(float scale);


		__forceinline static float DeltaTime() { return mDeltaTime * mScale; }

	private:
		// CPU ���� ������ ( 1�ʴ� �� �� )
		static LARGE_INTEGER mCPUFrequency;		// CPU ������
		static HWND mHwnd;
		static float mDeltaTime;
		static float mFpsTimer;

		// �߰��� ��Ʈ
		static float mScale;
		static double mdSecondPerCount;


		static long long mllBaseTime;		// ���� �ð����� ������ ó�� �����Ǿ��� ���� �ð�
		static long long mllPausedTime;		// �����־��� �ð�. ��, Stop()�� ȣ���� ��, Resume()�� ȣ���� ������ �ɸ� �ð�
		static long long mllStopTime;		// ���� �ð�. ��, Stop()�� ȣ������ ���� �ð�
		static long long mllPrevTime;		// ���� �ð�. ��, ���� Tick()�� �ð�.
		static long long mllCurrTime;		// ���� �ð�. ��, ���� Tick()�� �ð�.

		static bool mbIsStoped;
	};
}

