#pragma once
#include "Common.h"

namespace ya
{
	// 메인 프로그램이 될 녀석
	class Application
	{
	public:
		static Application& GetInstance()
		{
			static Application instance;
			return instance;
		}
		Application() = default;
		void Initialize(WindowData data);
		void Tick();
		void Release();
		WindowData GetWindowData() { return mWindowData; }
		__forceinline HDC GetHDC() { return mWindowData.hdc; }
		__forceinline HPEN GetPen(ePenColor color) { return mPens[static_cast<UINT>(color)]; }
		__forceinline HBRUSH GetBrush(eBrushColor color) { return mBrushes[static_cast<UINT>(color)]; }

	private:
		~Application();
		void initailizeWindow();
	private:
		WindowData mWindowData;
		HPEN mPens[static_cast<UINT>(ePenColor::COUNT)];
		HBRUSH mBrushes[static_cast<UINT>(eBrushColor::COUNT)];

	};
}

