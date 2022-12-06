#include "yaTitleScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaObject.h"
#include "yaStartButton.h"
#include "yaBGBlackBar.h"
#include "yaBGGmaeImage.h"
#include "yaBGGoldCount.h"
#include "yaExitButton.h"
#include "yaOptionButton.h"
#include "yaButtonImageObject.h"
namespace ya
{
	TitleScene::TitleScene()
		: mSceneType(eSceneType::TITLE_SCENE)
		, mbIsUpKeyDown(false)
		, mbIsDownKeyDown(false)
	{
		for (int i = 0; i < static_cast<int>(eTitleSceneMenu::COUNT); ++i)
		{
			mpButtons[i] = nullptr;
		}
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		ya::object::InstantiateAtAnotherScene<BGGmaeImage>(eColliderLayer::BACKGROUND, L"BGGmaeImage", L"Resources\\Image\\TitleBGResize.bmp", GetSceneTpye());
		ya::object::InstantiateAtAnotherScene<BGBlackBar>(eColliderLayer::BACKGROUND, L"BGBlackBar", L"Resources\\Image\\BlackBar.bmp", GetSceneTpye());
		ya::object::InstantiateAtAnotherScene<BGGoldCount>(eColliderLayer::BACKGROUND, L"BGGoldCount", L"Resources\\Image\\GoldCountBox.bmp", GetSceneTpye());
		
		mpButtons[static_cast<UINT>(eTitleSceneMenu::START)] = static_cast<ButtonImageObject*>(ya::object::InstantiateAtAnotherScene<StartButton>(eColliderLayer::BACKGROUND, L"BGStartButton", L"Resources\\Image\\StartButtonAlpha2.bmp", GetSceneTpye()));
		mpButtons[static_cast<UINT>(eTitleSceneMenu::OPTION)] = static_cast<ButtonImageObject*>(ya::object::InstantiateAtAnotherScene<OptionButton>(eColliderLayer::BACKGROUND, L"BGOptionButton", L"Resources\\Image\\OptionButtonAlpha.bmp", GetSceneTpye()));
		mpButtons[static_cast<UINT>(eTitleSceneMenu::EXIT)] = static_cast<ButtonImageObject*>(ya::object::InstantiateAtAnotherScene<ExitButton>(eColliderLayer::BACKGROUND, L"BGExitButton", L"Resources\\Image\\ExitButtonAlpha.bmp", GetSceneTpye()));
	}
	void TitleScene::Tick()
	{
		Scene::Tick();
		if (IS_KEY_DOWN(eKeyCode::W) || IS_KEY_DOWN(eKeyCode::UP) && !mbIsUpKeyDown)
		{
			if (!mpButtons[static_cast<UINT>(eTitleSceneMenu::EXIT)]->IsSelected())
			{
				mpButtons[static_cast<UINT>(eTitleSceneMenu::START)]->SetIsSelected(false);
				mpButtons[static_cast<UINT>(eTitleSceneMenu::OPTION)]->SetIsSelected(true);
				mbIsUpKeyDown = true;
			}
		}
		else if ((IS_KEY_DOWN(eKeyCode::D) || IS_KEY_DOWN(eKeyCode::RIGHT)) && mbIsUpKeyDown)
		{
			mpButtons[static_cast<UINT>(eTitleSceneMenu::OPTION)]->SetIsSelected(true);
			mpButtons[static_cast<UINT>(eTitleSceneMenu::EXIT)]->SetIsSelected(false);
			mpButtons[static_cast<UINT>(eTitleSceneMenu::START)]->SetIsSelected(false);
		}
		else if ((IS_KEY_DOWN(eKeyCode::A) || IS_KEY_DOWN(eKeyCode::LEFT)) && mbIsUpKeyDown)
		{
			mpButtons[static_cast<UINT>(eTitleSceneMenu::OPTION)]->SetIsSelected(false);
			mpButtons[static_cast<UINT>(eTitleSceneMenu::EXIT)]->SetIsSelected(true);
		}
		else if (IS_KEY_DOWN(eKeyCode::S) || IS_KEY_DOWN(eKeyCode::DOWN))
		{
			mpButtons[static_cast<UINT>(eTitleSceneMenu::START)]->SetIsSelected(true);
			mpButtons[static_cast<UINT>(eTitleSceneMenu::OPTION)]->SetIsSelected(false);
			mpButtons[static_cast<UINT>(eTitleSceneMenu::EXIT)]->SetIsSelected(false);
			mbIsUpKeyDown = false;
		}
		if (IS_KEY_UP(eKeyCode::N))
		{
			SceneManager::ChangeSecne(eSceneType::PLAY_SCENE);
		}

		if (IS_KEY_UP(eKeyCode::ENTER) || IS_KEY_UP(eKeyCode::SPACE))
		{
			for (int i = 0; i < static_cast<int>(eTitleSceneMenu::COUNT); ++i)
			{
				if (mpButtons[i]->IsSelected())
				{
					mpButtons[i]->ButtonClicked();
				}
			}
		}

	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t buffer[64];

		swprintf_s(buffer, 64, L"Title Scene");
		size_t strLen = wcsnlen_s(buffer, 64);

		TextOut(hdc, 10, 30, buffer, strLen);
	}
	void TitleScene::Enter()
	{
		Scene::Enter();
	}
	void TitleScene::Exit()
	{
		Scene::Exit();
	}
}