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
namespace ya
{
	TitleScene::TitleScene()
		: mSceneType(eSceneType::TITLE_SCENE)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		ya::object::InstantiateAtAnotherScene<BGGmaeImage>(eColliderLayer::BACKGROUND, L"BGGmaeImage", L"Resources\\Image\\TitleBGResize.bmp", GetSceneTpye());
		ya::object::InstantiateAtAnotherScene<StartButton>(eColliderLayer::BACKGROUND, L"BGStartButton", L"Resources\\Image\\StartButton.bmp", GetSceneTpye());
		ya::object::InstantiateAtAnotherScene<BGBlackBar>(eColliderLayer::BACKGROUND, L"BGBlackBar", L"Resources\\Image\\BlackBar.bmp", GetSceneTpye());
		ya::object::InstantiateAtAnotherScene<BGGoldCount>(eColliderLayer::BACKGROUND, L"BGGoldCount", L"Resources\\Image\\GoldCountBox.bmp", GetSceneTpye());
		ya::object::InstantiateAtAnotherScene<ExitButton>(eColliderLayer::BACKGROUND, L"BGExitButton", L"Resources\\Image\\ExitButton.bmp", GetSceneTpye());
		ya::object::InstantiateAtAnotherScene<OptionButton>(eColliderLayer::BACKGROUND, L"BGOptionButton", L"Resources\\Image\\OptionButton.bmp", GetSceneTpye());
	}
	void TitleScene::Tick()
	{
		Scene::Tick();
		if (IS_KEY_UP(eKeyCode::N))
		{
			SceneManager::ChangeSecne(eSceneType::PLAY_SCENE);
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