#include "yaTitleScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaStartButton.h"
#include "yaBGBlackBar.h"
#include "yaBGGmaeImage.h"
#include "yaBGGoldCount.h"
#include "yaExitButton.h"
#include "yaOptionButton.h"
#include "yaButtonImageObject.h"
#include "yaUIManager.h"
#include "yaBGTitleImage.h"
#include "yaResultImage.h"
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
		ya::object::InstantiateAtAnotherScene<BGTitleImage>(eColliderLayer::BACKGROUND, L"BGGmaeImage", L"Resources\\Image\\TitleBGResize.bmp", GetSceneTpye());
		ya::object::InstantiateAtAnotherScene<BGBlackBar>(eColliderLayer::BACKGROUND, L"BGBlackBar", L"Resources\\Image\\BlackBar.bmp", GetSceneTpye());
		ya::object::InstantiateAtAnotherScene<BGGoldCount>(eColliderLayer::BACKGROUND, L"BGGoldCount", L"Resources\\Image\\GoldCountBox.bmp", GetSceneTpye());
	}
	void TitleScene::Tick()
	{
		Scene::Tick();
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TitleScene::Enter()
	{
		Scene::Enter();
		UIManager::Push(eUIType::START_MENU_SELECTION);
	}
	void TitleScene::Exit()
	{
		//Scene::Exit();
	}
}