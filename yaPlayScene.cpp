#include "yaPlayScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaMudman.h"
#include "yaSceneManager.h"
#include "yaCollisionManager.h"
#include "yaObject.h"
#include "yaUIManager.h"
#include "yaHealthBar.h"
#include "yaPlaySceneHUDPanel.h"
#include "yaExpBar.h"

namespace ya
{
	PlayScene::PlayScene()
		: mSceneType(eSceneType::PLAY_SCENE)
		, mpPlayer(nullptr)
		, mbUiFlag(true)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		mpPlayer = ya::object::Instantiate<Player>(eColliderLayer::PLAYER);
		mpPlayer->SetPos({ 300.0f, 200.0f });
		int monsterCount = 15;
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<Mudman>(eColliderLayer::MONSTER, Vector2(100.f * i, 300.f), mpPlayer, GetSceneTpye());
		}
		CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		CollisionManager::SetLayer(eColliderLayer::MONSTER, eColliderLayer::PLAYER_PROJECTTILE, true);

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
		//if (IS_KEY_DOWN(eKeyCode::ESC))
		//{
		//	if (mbUiFlag)
		//	{
		//		UIManager::Pop(eUIType::PLAY_INFO_HUD);
		//		UIManager::Push(eUIType::PLAY_PAUSED);
		//	}
		//	else
		//	{
		//		UIManager::Pop(eUIType::PLAY_PAUSED);
		//		UIManager::Push(eUIType::PLAY_INFO_HUD);
		//	}
		//	mbUiFlag = !mbUiFlag;
		//}
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		char buffer[64];

		sprintf_s(buffer, 64, "Play Scene");
		size_t strLen = strnlen_s(buffer, 64);

		TextOutA(hdc, 10, 30, buffer, strLen);
	}
	void PlayScene::Enter()
	{
		Scene::Enter();
		CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		CollisionManager::SetLayer(eColliderLayer::MONSTER, eColliderLayer::PLAYER_PROJECTTILE, true);
		CollisionManager::SetLayer(eColliderLayer::GROUND, eColliderLayer::PLAYER, true);
		PlaySceneHUDPanel* pPanel = static_cast<PlaySceneHUDPanel*>(UIManager::GetUIInstanceOrNull(eUIType::PLAY_INFO_HUD));
		assert(pPanel != nullptr);
		pPanel->SetPlayerToHpBar(mpPlayer);
		pPanel->SetPlayerToExpBar(mpPlayer);
	}

	void PlayScene::Exit()
	{
		Scene::Exit();
	}
}