#include "yaUIManager.h"
#include "yaUIBase.h"
#include "yaButton.h"
#include "yaPanel.h"
#include "yaHealthBar.h"
#include "yaCharacterSelectionPanel.h"
#include "yaCharacterIcon.h"
#include "yaCharacterInfo.h"

namespace ya
{

	std::unordered_map<eUIType, UIBase*> UIManager::mUIMap;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UIBase*> UIManager::mUIStack;
	UIBase* UIManager::mpCurrUIBase = nullptr;

	void UIManager::Initialize()					// 여기에서 UI 메모리 할당
	{
		UIBase* pNewUI = new HealthBar();
		mUIMap.insert(std::make_pair(eUIType::PLAY_INFO_HUD, pNewUI));
		pNewUI->SetPos(Vector2(760.0f, 440.0f));
		pNewUI->LoadUIImage(L"HPBar", L"Resources\\Image\\HPBar.bmp");


		// CharacterSelection 파트
		UIBase* pSelect = new CharacterSelectionPanel(eUIType::CHARACTER_SELECTION);
		mUIMap.insert(std::make_pair(eUIType::CHARACTER_SELECTION, pSelect));
		pSelect->SetPos(Vector2(350.0f, BLACK_BAR_HEIGHT));
		pSelect->LoadUIImage(L"CharacterSelectionPanel", L"Resources\\Image\\CharacterSelectionPanelClean.bmp");
		pSelect->SetIsFullScreen(true);
		UIBase* pIcon = new CharacterIcon();
		pIcon->LoadUIImage(L"GennaroIcon", L"Resources\\Image\\Gennaro.bmp");
		pSelect->AddUIChild(pIcon);
		pIcon->SetPos(Vector2(CHARACTOR_ICON_X_DIFF, CHARACTOR_IOCN_Y_DIFF));
		UIBase* pInfo = new CharacterInfo();
		pInfo->LoadUIImage(L"GennaroInfo", L"Resources\\Image\\GennaroInfo.bmp");
		pSelect->AddUIChild(pInfo);
		pInfo->SetPos(Vector2(15.0f, 525.0f));



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
		// UI가 성공적으로 로드 되었다는 뜻이므로, UI 정보들을 화면에 그려줘야함.
		assert(pAddedUI != nullptr);

		pAddedUI->Initialize();
		pAddedUI->Active();
		pAddedUI->Tick();

		if (pAddedUI->GetIsFullScreen())
		{
			// 맨앞 UI 말고 나머지는 렌더 안하게 해주어야 함.
			// 즉, 나머지 UI를 싹 꺼주는게 맞음.
			std::stack<UIBase*> uiTmpStack = mUIStack;
			
			// 스택에서 하나씩 꺼내면서 전체화면인 애들 다 비활성화 해줌.
			while (!uiTmpStack.empty())
			{
				UIBase* pUIBase = uiTmpStack.top();
				uiTmpStack.pop();
				assert(pUIBase != nullptr);

				if (pUIBase->GetIsFullScreen())
					{ pUIBase->Inactive(); }
			}
		}

		// 전체화면 UI 다 끄고 난뒤, 새로 추가된 UI 스택에 Push
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
			// 요청된 UIType으로 로드 해주어야 함.
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
		// Pop할때는 내 현재 UI를 꺼주어야 함.
		// 근데 중요한게, 
		// 나는 OnLoadUIComplete()에서 추가된 UI를 제외한 나머지 풀스크린 UI를 전부 비활성화 했었음.
		// 이제 거꾸로 다시 켜주는 과정이 필요함.
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
				// Pop하는 uiType의 UI가 전체화면일 경우에, 
				// 남은 UI중에 전체화면이면서, 가장 상단의 UI를 활성화 해주어야만 함
				std::stack<UIBase*> uiBases = mUIStack;
				while (!uiBases.empty())
				{
					UIBase* pUIBase = uiBases.top();
					uiBases.pop();
					assert(pUIBase != nullptr);
					if (pUIBase->GetIsFullScreen())			// 전체화면인 가장 상단의 UI를 활성화 시켜주고 break
					{
						pUIBase->Active();			
						break;
					}
				}

				pUIBase->UIClear();
			}
			else											// UI 타입이 같지 않으면 tmpStack에다가 모아놓는다.
			{
				uiTmpStack.push(pUIBase);						
			}
		}

		// 원상복구
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