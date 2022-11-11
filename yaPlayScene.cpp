#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaMiniMudman.h"
#include "yaSceneManager.h"
#include "yaCollisionManager.h"
#include "yaObject.h"

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
		
		//int monsterCount = 100;
		//for (int i = 0; i < monsterCount; ++i)
		//{
		//	ya::object::InstantiateAtAnotherScene<Monster>(eColliderLayer::MONSTER, Vector2(50.f * i, 300.f), GetSceneTpye());
		//}
		////ya::object::Instantiate<Monster>(eColliderLayer::MONSTER, Vector2(200.f, 300.f));
		////ya::object::Instantiate<Monster>(eColliderLayer::MONSTER, Vector2(500.f, 300.f));
		//ya::object::Instantiate<Player>(eColliderLayer::PLAYER);
		//CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		//CollisionManager::SetLayer(eColliderLayer::MONSTER, eColliderLayer::PLAYER_PROJECTTILE, true);

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