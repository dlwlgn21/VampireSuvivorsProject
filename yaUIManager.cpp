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
#include "yaPlayScenePausedHUDPanel.h"
#include "yaPauseWeaponInfoBox.h"
#include "yaPausePlayerStartInfoBox.h"
#include "yaPauseUIContinueButton.h"
#include "yaPauseUIExitButton.h"
#include "yaPlaySceneLevelUpHUDPanel.h"
#include "yaLevelUpArrow.h"
#include "yaLevelUpHUDTop.h"
#include "yaLevelUpHUDMid.h"
#include "yaLevelUpHUDBot.h"
#include "yaPlayerLevelUpManager.h"
#include "yaPlayInfoIcon.h"
#include "yaLevelBoxIcon.h"
#include "yaPausePlayerWeponHUDBox.h"
#include "yaGameOverHUDPanel.h"
#include "yaGameOverTextHUD.h"
#include "yaGameOverExitHUD.h"

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

		UIBase* pWeaponBox = new WeaponBox(eUIType::PLAY_INFO_HUD);
		mUIMap.insert(std::make_pair(eUIType::PLAY_INFO_HUD, pWeaponBox));
		pPlayScenePanel->AddUIChild(pWeaponBox);
		PlayInfoIcon* pKnifeIcon = new PlayInfoIcon(eUIType::PLAY_INFO_HUD, ePlayInfoIconPos::TOP, eWeaponAndItemTypes::KNIFE, Vector2(-7.0f, 7.0f));
		pWeaponBox->AddUIChild(pKnifeIcon);
		LevelUpUIManager::GetInstance().SetPlayInfoWeaponBox(static_cast<WeaponBox*>(pWeaponBox));

		// PLAY_LEVEL_UP
		UIBase* pLevelUpPanel = new PlaySceneLevelUpHUDPanel();
		mUIMap.insert(std::make_pair(eUIType::PLAY_LEVEL_UP, pLevelUpPanel));

		UIBase* pLevelUpArrow = new LevelUpArrow();
		mUIMap.insert(std::make_pair(eUIType::PLAY_LEVEL_UP, pLevelUpArrow));
		pLevelUpPanel->AddUIChild(pLevelUpArrow);

		static_cast<PlaySceneLevelUpHUDPanel*>(pLevelUpPanel)->SetArrow(static_cast<LevelUpArrow*>(pLevelUpArrow));

		UIBase* pLevelUpTop = new LevelUpHUDTop();
		mUIMap.insert(std::make_pair(eUIType::PLAY_LEVEL_UP, pLevelUpTop));
		pLevelUpPanel->AddUIChild(pLevelUpTop);

		UIBase* pLevelUpMid = new LevelUpHUDMid();
		mUIMap.insert(std::make_pair(eUIType::PLAY_LEVEL_UP, pLevelUpMid));
		pLevelUpPanel->AddUIChild(pLevelUpMid);

		UIBase* pLevelUpBot = new LevelUpHUDBot();
		mUIMap.insert(std::make_pair(eUIType::PLAY_LEVEL_UP, pLevelUpBot));
		pLevelUpPanel->AddUIChild(pLevelUpBot);
		const float LEVEL_IMG_X_DIFF = 16.0f;
		const float LEVEL_IMG_Y_DIFF = 156.0f;
		pLevelUpTop->SetPos(Vector2(LEVEL_IMG_X_DIFF, LEVEL_IMG_Y_DIFF));
		pLevelUpMid->SetPos(Vector2(LEVEL_IMG_X_DIFF, LEVEL_IMG_Y_DIFF + LEVEL_IMG_HEIGHT));
		pLevelUpBot->SetPos(Vector2(LEVEL_IMG_X_DIFF, LEVEL_IMG_Y_DIFF + LEVEL_IMG_HEIGHT * 2));



		// PLAY_PAUSED Section
		UIBase* pPlayPausedPanel = new PlayScenePausedHUDPanel();
		mUIMap.insert(std::make_pair(eUIType::PLAY_PAUSED, pPlayPausedPanel));

		UIBase* pContinueButton = new PauseUIContinueButton();
		mUIMap.insert(std::make_pair(eUIType::PLAY_PAUSED, pContinueButton));
		pPlayPausedPanel->AddUIChild(pContinueButton);

		UIBase* pPauseExitButton = new PauseUIExitButton();
		mUIMap.insert(std::make_pair(eUIType::PLAY_PAUSED, pPauseExitButton));
		pPlayPausedPanel->AddUIChild(pPauseExitButton);
		static_cast<PlayScenePausedHUDPanel*>(pPlayPausedPanel)->SetButtonPtrs();

		UIBase* pPausInfoBox = new PauseWeaponInfoBox();
		mUIMap.insert(std::make_pair(eUIType::PLAY_PAUSED, pPausInfoBox));
		pPlayPausedPanel->AddUIChild(pPausInfoBox);


		PlayInfoIcon* pKnifePauseIcon = new PlayInfoIcon(eUIType::PLAY_PAUSED, ePlayInfoIconPos::TOP, eWeaponAndItemTypes::KNIFE, Vector2(90.0f, 7.0f));
		pPausInfoBox->AddUIChild(pKnifePauseIcon);

		LevelBoxIcon* pLevelBoxIcon = new LevelBoxIcon();
		pKnifePauseIcon->AddUIChild(pLevelBoxIcon);
		pLevelBoxIcon->SetPos(Vector2(108.0f + 42.0f, 90.0f + 14.0f));

		UIBase* pPlayerWeaponHUDInfo = new PausePlayerWeponHUDBox();
		mUIMap.insert(std::make_pair(eUIType::PLAY_PAUSED, pPlayerWeaponHUDInfo));
		pPlayPausedPanel->AddUIChild(pPlayerWeaponHUDInfo);

		UIBase* pPlayerStatInfo = new PausePlayerStartInfoBox();
		mUIMap.insert(std::make_pair(eUIType::PLAY_PAUSED, pPlayerStatInfo));
		pPlayPausedPanel->AddUIChild(pPlayerStatInfo);

		LevelUpUIManager::GetInstance().SetPlayPauseWeaponBox(static_cast<PauseWeaponInfoBox*>(pPausInfoBox));

		//GameOverUI
		UIBase* pGameOverHUD = new GameOverHUDPanel();
		mUIMap.insert(std::make_pair(eUIType::GAME_OVER, pGameOverHUD));
		UIBase* pGameOverTextHUD = new GameOverTextHUD();
		pGameOverHUD->AddUIChild(pGameOverTextHUD);
		UIBase* pGameOverExitHUD = new GameOverExitHUD();
		pGameOverHUD->AddUIChild(pGameOverExitHUD);


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
				{
					pUIBase->Inactive();
				}
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
		{
			return;
		}

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