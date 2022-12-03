#include "yaUIManager.h"
#include "yaUIBase.h"
#include "yaButton.h"
#include "yaPanel.h"
#include "yaHealthBar.h"

namespace ya
{

	std::unordered_map<eUIType, UIBase*> UIManager::mUIMap;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UIBase*> UIManager::mUIStack;
	UIBase* UIManager::mpCurrUIBase = nullptr;

	void UIManager::Initialize()					// ���⿡�� UI �޸� �Ҵ�
	{
		UIBase* pNewUI = new HealthBar();
		mUIMap.insert(std::make_pair(eUIType::HP, pNewUI));
		pNewUI->SetPos(Vector2(760.0f, 440.0f));
		pNewUI->LoadUIImage(L"HPBar", L"Resources\\Image\\HPBar.bmp");


		//pNewUI->SetSize(Vector2(500.0f, 100.0f));
		//UIBase* pHpBar = new Button(eUIType::HP);
		//mUIMap.insert(std::make_pair(eUIType::HP, pHpBar));
		//pHpBar->SetPos(Vector2(0.0f, 50.0f));
		//pHpBar->LoadUIImage(L"HPBar", L"Resources\\Image\\HPBar.bmp");

		//UIBase* pNewUI = new Panel(eUIType::INVENTORY);
		//mUIMap.insert(std::make_pair(eUIType::INVENTORY, pNewUI));
		//pNewUI->LoadUIImage(L"Backpack", L"Resources\\Image\\Backpack.bmp");
		//pNewUI->SetPos(Vector2(500.0f, 500.0f));

		//pNewUI->AddUIChild(pHpBar);

		//pNewUI = new Button(eUIType::OPTIOIN);
		//mUIMap.insert(std::make_pair(eUIType::OPTIOIN, pNewUI));
		////pNewUI->SetIsFullScreen(true);
	}
	void UIManager::LoadUI(eUIType uiType)
	{
		auto iter = mUIMap.find(uiType);
		if (iter == mUIMap.end())
		{
			OnLoadUIFail();
			return;
		}
		OnLoadUIComplete(iter->second);
	}

	void UIManager::OnLoadUIFail()
	{
		mpCurrUIBase = nullptr;
		assert(false);
	}

	void UIManager::OnLoadUIComplete(UIBase* pAddedUI)
	{
		// UI�� ���������� �ε� �Ǿ��ٴ� ���̹Ƿ�, UI �������� ȭ�鿡 �׷������.
		assert(pAddedUI != nullptr);

		pAddedUI->Initialize();
		pAddedUI->Active();
		pAddedUI->Tick();

		if (pAddedUI->GetIsFullScreen())
		{
			// �Ǿ� UI ���� �������� ���� ���ϰ� ���־�� ��.
			// ��, ������ UI�� �� ���ִ°� ����.
			std::stack<UIBase*> uiTmpStack = mUIStack;
			
			// ���ÿ��� �ϳ��� �����鼭 ��üȭ���� �ֵ� �� ��Ȱ��ȭ ����.
			while (!uiTmpStack.empty())
			{
				UIBase* pUIBase = uiTmpStack.top();
				uiTmpStack.pop();
				assert(pUIBase != nullptr);

				if (pUIBase->GetIsFullScreen())
					{ pUIBase->Inactive(); }
			}
		}

		// ��üȭ�� UI �� ���� ����, ���� �߰��� UI ���ÿ� Push
		mUIStack.push(pAddedUI);
	}

	void UIManager::Tick()
	{
		std::stack<UIBase*> uiTmpStack = mUIStack;
		while (!uiTmpStack.empty())
		{
			UIBase* pUIBase = uiTmpStack.top();
			assert(pUIBase != nullptr);
			pUIBase->Tick();
			uiTmpStack.pop();
		}

		if (mRequestUIQueue.size() > 0)
		{
			// ��û�� UIType���� �ε� ���־�� ��.
			eUIType requestUiType = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			LoadUI(requestUiType);
		}
	}
	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiTmpStack = mUIStack;
		while (!uiTmpStack.empty())
		{
			UIBase* pUIBase = uiTmpStack.top();
			assert(pUIBase != nullptr);
			pUIBase->Render(hdc);
			uiTmpStack.pop();
		}
	}

	void UIManager::Push(eUIType uiType)
	{
		mRequestUIQueue.push(uiType);
	}
	void UIManager::Pop(eUIType uiType)
	{
		// Pop�Ҷ��� �� ���� UI�� ���־�� ��.
		// �ٵ� �߿��Ѱ�, 
		// ���� OnLoadUIComplete()���� �߰��� UI�� ������ ������ Ǯ��ũ�� UI�� ���� ��Ȱ��ȭ �߾���.
		// ���� �Ųٷ� �ٽ� ���ִ� ������ �ʿ���.
		if (mUIStack.size() <= 0) 
			{ return; }

		std::stack<UIBase*> uiTmpStack;

		UIBase* pUIBase = nullptr;
		while (!mUIStack.empty())
		{
			pUIBase = mUIStack.top();
			mUIStack.pop();
			assert(pUIBase != nullptr);
			if (pUIBase->GetType() == uiType && pUIBase->GetIsFullScreen())
			{
				// Pop�ϴ� uiType�� UI�� ��üȭ���� ��쿡, 
				// ���� UI�߿� ��üȭ���̸鼭, ���� ����� UI�� Ȱ��ȭ ���־�߸� ��
				std::stack<UIBase*> uiBases = mUIStack;
				while (!uiBases.empty())
				{
					UIBase* pUIBase = uiBases.top();
					uiBases.pop();
					assert(pUIBase != nullptr);
					if (pUIBase->GetIsFullScreen())			// ��üȭ���� ���� ����� UI�� Ȱ��ȭ �����ְ� break
					{
						pUIBase->Active();			
						break;
					}
				}

				pUIBase->UIClear();
			}
			else											// UI Ÿ���� ���� ������ tmpStack���ٰ� ��Ƴ��´�.
			{
				uiTmpStack.push(pUIBase);						
			}
		}

		// ���󺹱�
		while (!uiTmpStack.empty())
		{
			pUIBase = uiTmpStack.top();
			assert(pUIBase != nullptr);
			mUIStack.push(pUIBase);
			uiTmpStack.pop();
		}
	}

	void UIManager::Release()
	{
		for (auto iter = mUIMap.begin(); iter != mUIMap.end(); ++iter)
		{
			if (iter->second != nullptr) { delete iter->second; }
		}
		mUIMap.clear();
	}
	UIBase* UIManager::GetUIInstanceOrNull(eUIType type)
	{
		auto iter = mUIMap.find(type);
		if (iter == mUIMap.end())
		{
			return nullptr;
		}
		return iter->second;
	}
}