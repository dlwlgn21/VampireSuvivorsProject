#include "yaTime.h"
#include "yaApplication.h"

namespace ya
{
	LARGE_INTEGER Time::mCPUFrequency;
	float Time::mDeltaTime = 0.0f;
	float Time::mFpsTimer = 0.0f;
	HWND Time::mHwnd;

	float Time::mScale = 1.0f;
	double Time::mdSecondPerCount{ 0.0 };
	long long Time::mllBaseTime{ 0 };
	long long Time::mllPausedTime{ 0 };
	long long Time::mllStopTime{ 0 };
	long long Time::mllPrevTime{ 0 };
	long long Time::mllCurrTime{ 0 };
	bool Time::mbIsStoped = false;

	void Time::Initialize()
	{
		// �ý����� ���� ī���ʹ� ���ļ� ���·� ���� ��ȯ�Ѵ�. ������ �츮���� �ʿ��� ���� �ð�!
		// ����, ���ļ�(Hz)���¸� ���ؿͼ� ������ 1 Cycle �� ��� �ð��� ���صд�.
		// �� ���� ������ �ʴ� ������ ������ ���ؿ� ���ļ��� �� ���� ���ϸ�, ���ϴ� �ð�(��)�� ���� �� �ְ� ��.
		
		QueryPerformanceFrequency(&mCPUFrequency);			// CPU �ʴ� �ݺ� �Ǵ� �������� ������ �Լ� ó���� 0��.


		//QueryPerformanceCounter(&mPrevFrequency);			// ���α׷� ���� ���� ���� CPU�� Ŭ���� 
		
		// ADD PART
		mdSecondPerCount = 1.0 / static_cast<double>(mCPUFrequency.QuadPart);
		

		// ADD PART END

		mHwnd = Application::GetInstance().GetWindowData().hwnd;


	}

	void Time::Tick()
	{
		//QueryPerformanceCounter(&mCurFrequency);
		//float differntFrequency
		//	= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		//mDeltaTime = differntFrequency / mCPUFrequency.QuadPart;
		//mPrevFrequency.QuadPart = mCurFrequency.QuadPart;	// ����

		// ADD PART
		if (mbIsStoped)
		{
			mDeltaTime = 0.0f;
			return;
		}

		long long currTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

		mllCurrTime = currTime;
		mDeltaTime = static_cast<float>((mllCurrTime - mllPrevTime) * mdSecondPerCount);
		mllPrevTime = mllCurrTime;
		if (mDeltaTime < 0.0f)
		{
			mDeltaTime = 0.0f;
		}
	}

	void Time::Render(HDC hdc)
	{
		mFpsTimer += Time::DeltaTime();
		//if (mTime > 1.0f)
		//{
		//	wchar_t buffer[64] = {};

		//	// DeltaTime == �� ������ ���µ� �ɸ� �ð�.
		//	float fps = 1.0f / mDeltaTime;
		//	swprintf_s(buffer, 64, L"FramePerSecond : %.0f", fps);
		//	size_t strLen = wcsnlen_s(buffer, 64);
		//	TextOut(hdc, 10, 10, buffer, static_cast<int>(strLen));
		//	HWND hWnd
		//		= Application::GetInstance().GetWindowData().hwnd;
		//	//SetWindowTextW(mHwnd, buffer);
		//	mTime = 0.0f;
		//}
		if (mFpsTimer >= 0.1f)
		{
			wchar_t buffer[64] = {};
			// DeltaTime == �� ������ ���µ� �ɸ� �ð�.
			float fps = 1.0f / mDeltaTime;
			swprintf_s(buffer, 64, L"FramePerSecond : %.0f", fps);
			size_t strLen = wcsnlen_s(buffer, 64);
			TextOutW(hdc, 10, 10, buffer, static_cast<int>(strLen));

			swprintf_s(buffer, 64, L"Total Time == %.0f", TotalTime());
			strLen = wcsnlen_s(buffer, 64);
			TextOutW(hdc, 30, 30, buffer, static_cast<int>(strLen));
			//HWND hWnd
			//	= Application::GetInstance().GetWindowData().hwnd;
			//SetWindowTextW(mHwnd, buffer);
			mFpsTimer = 0.0f;
		}
	}

	void Time::StartTimeCounting()
	{
		long long currTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

		mllBaseTime = currTime;
		mllPrevTime = currTime;
		mllStopTime = 0;
		mbIsStoped = false;
	}

	void Time::Reset()
	{
		long long currTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));
		mllBaseTime = 0;
		mllPrevTime = currTime;
		mllStopTime = 0;
		mbIsStoped = false;
	}

	void Time::Stop()
	{
		if (!mbIsStoped)
		{
			long long currTime;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

			mllStopTime = currTime;
			mbIsStoped = true;
		}
	}

	void Time::Resume()
	{
		long long startTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

		if (mbIsStoped)
		{
			mllPausedTime += (startTime - mllStopTime);

			mllPrevTime = startTime;
			mllStopTime = 0;
			mbIsStoped = false;
		}

	}

	float Time::TotalTime()
	{
		if (mbIsStoped)
			{ return static_cast<float>(((mllStopTime - mllPausedTime) - mllBaseTime) * mdSecondPerCount); }
		else
			{ return static_cast<float>(((mllCurrTime - mllPausedTime) - mllBaseTime) * mdSecondPerCount); }
	}

	void Time::SetScale(float scale)
	{
		mScale = scale;
	}

}