#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaMonster.h"
#include "yaSceneManager.h"
#include "yaCollisionManager.h"

namespace ya
{
	PlayScene::PlayScene()
		: mSceneType(eSceneType::PLAY_SCENE)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		/*BgImageObject* bg = new BgImageObject();
		AddGameObject(bg);*/
		//AddGameObject(new Player(), eColliderLayer::PLAYER);
		//AddGameObject(new Monster(), eColliderLayer::MONSTER);
		//CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		//Scene::Initialize();

	}
	void PlayScene::Tick()
	{
		Scene::Tick();
		if (IS_KEY_UP(eKeyCode::N))
		{
			SceneManager::ChangeSecne(eSceneType::ENDING_SCENE);
		}
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t buffer[64];

		swprintf_s(buffer, 64, L"Play Scene");
		size_t strLen = wcsnlen_s(buffer, 64);

		TextOut(hdc, 10, 30, buffer, strLen);
	}
	void PlayScene::Enter()
	{
		Scene::Enter();
	}

	void PlayScene::Exit()
	{
		Scene::Exit();
	}
}