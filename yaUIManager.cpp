#include "yaUIManager.h"
#include "yaUIBase.h"
#include "yaButton.h"
#include "yaPanel.h"
#include "yaHealthBar.h"
#include "yaCharacterSelectionPanel.h"
#include "yaCharacterIcon.h"
#include "yaCharacterInfo.h"
#include "yaTitleSceneStartUIButton.h"
#include "yaTitleSceneOptionUIButton.h"
#include "yaTitleSceneExitUIButton.h"
#include "yaCharacterWordButton.h"
#include "yaStartMenuPanel.h"
#include "yaStageSelectionPanel.h"
#include "yaStageLibraryIcon.h"
#include "yaPlaySceneHUDPanel.h"
#include "yaWeaponBox.h"
#include "yaExpBar.h"

namespace ya
{
	std::unordered_map<eUIType, UIBase*> UIManager::mUIMap;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UIBase*> UIManager::mUIStack;
	UIBase* UIManager::mpCurrUIBase = nullptr;

	void UIManager::Initialize()					// 여기에서 UI 메모리 할당
	{
		// TitleSceneUIButton Section
		StartMenuPanel* pStartMenuPanel = new StartMenuPanel();
		mUIMap.insert(std::make_pair(eUIType::START_MENU_SELECTION, pStartMenuPanel));
		UIBase* pStartButton = new TitleSceneStartUIButton();
		mUIMap.insert(std::make_pair(eUIType::START_MENU_SELECTION, pStartButton));
		UIBase* pOptionButton = new TitleSceneOptionUIButton();
		mUIMap.insert(std::make_pair(eUIType::START_MENU_SELECTION, pOptionButton));
		UIBase* pExitButton = new TitleSceneExitUIButton();
		mUIMap.insert(std::make_pair(eUIType::START_MENU_SELECTION, pExitButton));

		pStartMenuPanel->AddUIChild(pStartButton);
		pStartMenuPanel->AddUIChild(pOptionButton);
		pStartMenuPanel->AddUIChild(pExitButton);
		pStartButton->SetPos(Vector2(SCREEN_WIDTH / 2.0f - static_cast<UIAnimObject*>(pStartButton)->GetSize().x / 2, SCREEN_HEIGHT / 2 + 100.0f));
		pOptionButton->SetPos(Vector2(SCREEN_WIDTH / 2.0f + static_cast<UIAnimObject*>(pOptionButton)->GetSize().x * 2, 5.0f));
		pExitButton->SetPos(Vector2(SCREEN_WIDTH / 2.0f - static_cast<UIAnimObject*>(pExitButton)->GetSize().x * 3, 5.0f));
		pStartMenuPanel->SetButtonPtr();



		// CharacterSelection Section
		UIBase* pSelect = new CharacterSelectionPanel(eUIType::CHARACTER_SELECTION);
		mUIMap.insert(std::make_pair(eUIType::CHARACTER_SELECTION, pSelect));
		pSelect->SetPos(Vector2(SCREEN_WIDTH / 2 - pSelect->GetSize().x / 2, BLACK_BAR_HEIGHT));
		UIBase* pIcon = new CharacterIcon();
		pSelect->AddUIChild(pIcon);
		pIcon->SetPos(Vector2(CHARACTOR_ICON_X_DIFF, CHARACTOR_IOCN_Y_DIFF));
		UIBase* pInfo = new CharacterInfo();
		pSelect->AddUIChild(pInfo);
		pInfo->SetPos(Vector2(15.0f, 800.0f));
		UIBase* pWordButton = new CharacterWordButton();
		pSelect->AddUIChild(pWordButton);
		pWordButton->SetPos(Vector2(880.0f, 800.0f));


		// StageSelection Section
		UIBase* pStageSelection = new StageSelectionPanel();
		mUIMap.insert(std::make_pair(eUIType::STAGE_SELECTION, pStageSelection));
		pStageSelection->SetPos(Vector2(SCREEN_WIDTH / 2 - pStageSelection->GetSize().x / 2, BLACK_BAR_HEIGHT));
		UIBase* pStageIcon = new StageLibraryIcon();
		pStageSelection->AddUIChild(pStageIcon);
		pStageIcon->SetPos(Vector2(CHARACTOR_ICON_X_DIFF + 15.0f, CHARACTOR_IOCN_Y_DIFF + 30.0f));
		UIBase* pStageButton = new CharacterWordButton();
		pStageSelection->AddUIChild(pStageButton);
		pStageButton->SetPos(Vector2(880.0f, 800.0f));


		// PLAY_INFO_HUD Section
		UIBase* pPlayScenePanel = new PlaySceneHUDPanel();
		mUIMap.insert(std::make_pair(eUIType::PLAY_INFO_HUD, pPlayScenePanel));

		UIBase* pHpBar = new HealthBar();
		mUIMap.insert(std::make_pair(eUIType::PLAY_INFO_HUD, pHpBar));
		pPlayScenePanel->AddUIChild(pHpBar);

		UIBase* pEXPBar = new ExpBar();
		mUIMap.insert(std::make_pair(eUIType::PLAY_INFO_HUD, pEXPBar));
		pPlayScenePanel->AddUIChild(pEXPBar);

		UIBase* pWeaponBox = new WeaponBox();
		mUIMap.insert(std::make_pair(eUIType::PLAY_INFO_HUD, pWeaponBox));
		pPlayScenePanel->AddUIChild(pWeaponBox);


		//pNewUI->SetSize(Vector2(500.0f, 100.0f));
		//UIBase* pHpBar = new Button(eUIType::HP);
		//mUIMap.insert(std::make_pair(eUIType::HP, pHpBar));[
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

		// 전체화면 UI 다 끄고 난뒤, UI 스택에 Push
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
		// 기존
		//std::stack<UIBase*> uiTmpStack = mUIStack;
		//while (!uiTmpStack.empty())
		//{
		//	UIBase* pUIBase = uiTmpStack.top();
		//	assert(pUIBase != nullptr);
		//	pUIBase->Render(hdc);
		//	uiTmpStack.pop();
		//}

		std::stack<UIBase*> tmpStack = mUIStack;
		std::stack<UIBase*> tmpShowStack;

		// 뒤집어서 렌더링을 해준다.
		while (!tmpStack.empty())
		{
			UIBase* pUIBase = tmpStack.top();
			tmpShowStack.push(pUIBase);
			tmpStack.pop();
		}

		while (!tmpShowStack.empty())
		{
			UIBase* pUIBase = tmpShowStack.top();
			if (pUIBase != nullptr)
			{
				pUIBase->Render(hdc);
			}
			tmpShowStack.pop();
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