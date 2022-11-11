#include "yaTitleScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaBgImageObject.h"
#include "yaBGImageObjectAlpha.h"
#include "yaSceneManager.h"
#include "yaObject.h"
#include "yaButtonImageObject.h"

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
		ya::object::InstantiateAtAnotherScene<BGImageObject>(eColliderLayer::BACKGROUND, L"TitleBG.bmp", GetSceneTpye());

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