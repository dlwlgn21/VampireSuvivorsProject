#pragma once
#include "Common.h"
/*
UI�� Ư¡
	�÷��̾��� ���ۿ� ������ ���� �ʴ´� (��ġ ��)
UI�� ���캸��..
1. ��üȭ�� UI
2. �⺻ UI
	2.1 HUD				(���ھ�, �������� ǥ�����ִ� UI)
	2.2 Button			(�������� ��ȣ�ۿ��� �� �� �ִ� UI)
�䷱������ �����Ǿ� �ִ�.

��, UI->UI�ڽı����� �������� �ٸ� UI���� �����ؼ�
���� �����̴� �ϳ��� ū UI�� �����ؾ� �Ѵ�.
	
�κ��丮�� ��� ��ư�� 2���� �迭�� �����س��� ������ �� �� �ִ�.
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

