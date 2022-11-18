#include "yaUIManager.h"
#include "yaHUD.h"

namespace ya
{

	std::unordered_map<eUIType, UIBase*> UIManager::mUIMap;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UIBase*> UIManager::mUIStack;
	UIBase* UIManager::mpCurrUIBase = nullptr;

	void UIManager::Initialize()					// 여기에서 UI 메모리 할당
	{
		UIBase* pNewUI = new HUD(eUIType::HP);
		mUIMap.insert(std::make_pair(eUIType::HP, pNewUI));
		pNewUI->SetPos(Vector2(100.0f, 100.0f));
		pNewUI->SetSize(Vector2(500.0f, 100.0f));
		pNewUI->LoadUIImage(L"HPBar", L"Resources\\Image\\HPBar.bmp");


		pNewUI = new UIBase(eUIType::MP);
		mUIMap.insert(std::make_pair(eUIType::MP, pNewUI));

		pNewUI = new UIBase(eUIType::INVENTORY);
		mUIMap.insert(std::make_pair(eUIType::INVENTORY, pNewUI));
		pNewUI->SetIsFullScreen(true);

		pNewUI = new UIBase(eUIType::OPTIOIN);
		mUIMap.insert(std::make_pair(eUIType::OPTIOIN, pNewUI));
		pNewUI->SetIsFullScreen(true);

		pNewUI = new UIBase(eUIType::SHOP);
		mUIMap.insert(std::make_pair(eUIType::SHOP, pNewUI));

	}
	void UIManager::OnLoad(eUIType uiType)
	{
		auto iter = mUIMap.find(uiType);
		if (iter == mUIMap.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}

	void UIManager::OnFail()
	{
		mpCurrUIBase = nullptr;
	}

	void UIManager::OnComplete(UIBase* pAddedUI)
	{
		// UI 정보들을 화면에 그려줘야함.
		if (pAddedUI == nullptr) { assert(false); return; }

		pAddedUI->Initialize();
		pAddedUI->Activate();
		pAddedUI->Tick();

		if (pAddedUI->GetIsFullScreen())
		{
			// 맨앞 UI 말고 나머지는 렌더 안하게 해주어야 함.
			std::stack<UIBase*> uiBases = mUIStack;
			while (!uiBases.empty())
			{
				UIBase* pUIBase = uiBases.top();
				uiBases.pop();
				assert(pUIBase != nullptr);
				if (pUIBase->GetIsFullScreen())
				{ pUIBase->InActivate(); }
			}
		}
		mUIStack.push(pAddedUI);
	}

	void UIManager::Tick()
	{
		std::stack<UIBase*> uiBases = mUIStack;
		while (!uiBases.empty())
		{
			UIBase* pUIBase = uiBases.top();
			assert(pUIBase != nullptr);
			pUIBase->Tick();
			uiBases.pop();
		}

		if (mRequestUIQueue.size() > 0)
		{
			// UI 로드 해주어야 함.
			eUIType requestUiType = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			OnLoad(requestUiType);
		}
	}
	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBases = mUIStack;
		while (!uiBases.empty())
		{
			UIBase* pUIBase = uiBases.top();
			assert(pUIBase != nullptr);
			pUIBase->Render(hdc);
			uiBases.pop();
		}
	}

	void UIManager::Push(eUIType uiType)
	{
		mRequestUIQueue.push(uiType);
	}
	void UIManager::Pop(eUIType uiType)
	{
		if (mUIStack.size() <= 0) { return; }

		std::stack<UIBase*> tmpStack;

		UIBase* pUIBase = nullptr;
		while (!mUIStack.empty())
		{
			pUIBase = mUIStack.top();
			mUIStack.pop();
			assert(pUIBase != nullptr);
			// Pop하는 UI가 전체화면일 경우에, 남은 UI중에 전체화면인 가장 상단의 UI를 활성화 해주어야만 함
			if (pUIBase->GetType() == uiType && pUIBase->GetIsFullScreen())
			{
				std::stack<UIBase*> uiBases = mUIStack;
				while (!uiBases.empty())
				{
					UIBase* pUIBase = uiBases.top();
					uiBases.pop();
					assert(pUIBase != nullptr);
					if (pUIBase->GetIsFullScreen())			// 전체화면인 가장 상단의 UI를 활성화 시켜주고 break
					{
						pUIBase->Activate();			
						break;
					}
				}
				pUIBase->UIClear();
			}
			else
			{
				tmpStack.push(pUIBase);						// UI 타입이 같지 않으면 tmpStack에다가 모아놓는다.
			}
		}

		// 원상복구
		while (!tmpStack.empty())
		{
			pUIBase = tmpStack.top();
			assert(pUIBase != nullptr);
			mUIStack.push(pUIBase);
			tmpStack.pop();
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
	UIBase* UIManager::GetUIInstance(eUIType type)
	{
		auto res = mUIMap.find(type);
		return res->second;
	}
}