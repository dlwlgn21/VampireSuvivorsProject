#pragma once
#include "Common.h"
#include "yaUIBase.h"

/*
UI�� Ư¡
	�÷��̾��� ���ۿ� ������ ���� �ʴ´� (��ġ ��)
	
UI�� ���캸��..
1. ��üȭ�� UI
2. �⺻ UI
	2.1 HUD (���ھ�, �������� ǥ�����ִ� UI)
	2.2 Button
�䷱������ �����Ǿ� �ִ�.

��, �� UI �� �ڽı����� �������� �ٸ� UI���� �����ؼ�
���� �����̴� �ϳ��� ū UI�� �����ؾ� �Ѵ�.
	
�κ��丮�� ��� ��ư�� 2���� �迭�� �����س��� ������ �� �� �ִ�.

*/

namespace ya
{
	class UIManager
	{
	public:
		static void Initialize();
		static void OnLoad(eUIType uiType);
		static void Tick();
		static void Render(HDC hdc);
		static void OnComplete(UIBase* pAddedUIType);
		static void OnFail();

		static void Push(eUIType uiType);
		static void Pop(eUIType uiType);

		static void Release();
	private:
		static std::unordered_map<eUIType, UIBase*> mUIMap;
		static std::queue<eUIType> mRequestUIQueue;
		static std::stack<UIBase*> mUIStack;
		static UIBase* mpCurrUIBase;
	};
}

