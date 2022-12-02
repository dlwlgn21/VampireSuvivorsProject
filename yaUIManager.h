#pragma once
#include "Common.h"
/*
UI의 특징
	플레이어의 조작에 영향을 받지 않는다 (위치 등)
UI를 살펴보면..
1. 전체화면 UI
2. 기본 UI
	2.1 HUD				(스코어, 정보등을 표시해주는 UI)
	2.2 Button			(유저와의 상호작용을 할 수 있는 UI)
요런식으로 구성되어 있다.

즉, UI->UI자식구조로 여러가지 다른 UI들을 구성해서
같이 움직이는 하나의 큰 UI로 구성해야 한다.
	
인벤토리도 사실 버튼을 2차원 배열로 세팅해놓은 것으로 볼 수 있다.
*/

namespace ya
{
	class UIBase;
	class UIManager
	{
	public:
		static void Initialize();
		static void LoadUI(eUIType uiType);
		static void Tick();
		static void Render(HDC hdc);
		static void OnLoadUIComplete(UIBase* pAddedUI);
		static void OnLoadUIFail();

		static void Push(eUIType uiType);
		static void Pop(eUIType uiType);

		static void Release();
		static UIBase* GetUIInstanceOrNull(eUIType type);

	private:
		static std::unordered_map<eUIType, UIBase*> mUIMap;
		static std::queue<eUIType> mRequestUIQueue;
		static std::stack<UIBase*> mUIStack;
		static UIBase* mpCurrUIBase;
	};
}

