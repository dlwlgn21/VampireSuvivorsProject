#include "yaTime.h"
#include "yaApplication.h"

namespace ya
{

	LARGE_INTEGER Time::mCPUFrequency;
	LARGE_INTEGER Time::mPrevFrequency;
	LARGE_INTEGER Time::mCurFrequency;
	float Time::mDeltaTime = 0.0f;
	float Time::mTime = 0.0f;
	HWND Time::mHwnd;
	void Time::Initialize()
	{
		QueryPerformanceFrequency(&mCPUFrequency);			// CPU �ʴ� �ݺ� �Ǵ� �������� ������ �Լ� ó���� 0��.
		QueryPerformanceCounter(&mPrevFrequency);			// ���α׷� ���� ���� ���� CPU�� Ŭ���� 
		mHwnd = Application::GetInstance().GetWindowData().hwnd;
	}

	void Time::Tick()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differntFrequency
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		mDeltaTime = differntFrequency / mCPUFrequency.QuadPart;


		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;	// ����
	}

	void Time::Render(HDC hdc)
	{
		mTime += Time::DeltaTime();
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
		wchar_t buffer[64] = {};

		// DeltaTime == �� ������ ���µ� �ɸ� �ð�.
		float fps = 1.0f / mDeltaTime;
		swprintf_s(buffer, 64, L"FramePerSecond : %.0f", fps);
		size_t strLen = wcsnlen_s(buffer, 64);
		TextOutW(hdc, 10, 10, buffer, static_cast<int>(strLen));
		HWND hWnd
			= Application::GetInstance().GetWindowData().hwnd;
		//SetWindowTextW(mHwnd, buffer);
		mTime = 0.0f;
	}

}