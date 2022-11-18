#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaUIManager.h"

#include "yaBgImageObject.h"
#include "yaBoomGhost.h"
#include "yaDurahanBoneKnight.h"
#include "yaGreenGhost.h"
#include "yaGrayMira.h"
#include "yaGreenMedusaHead.h"
#include "yaMiniMudman.h"
#include "yaHUD.h"

//#include "yaGround.h"


#include "yaObject.h"
#include "yaCollisionManager.h"
#include "yaApplication.h"
#include "yaToolScene.h"
namespace ya
{
	LogoScene::LogoScene()
		: mSceneType(eSceneType::LOGO_SCENE)
	{
	}
	LogoScene::~LogoScene()
	{
	}
	void LogoScene::Initialize()
	{
		int monsterCount = 5;
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<MiniMudman>(eColliderLayer::MONSTER, Vector2(100.f * i, 300.f), GetSceneTpye());
		}

		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BoomGhost>(eColliderLayer::MONSTER, Vector2(100.f * i, 800.f), GetSceneTpye());
		}
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<GreenGhost>(eColliderLayer::MONSTER, Vector2(100.f * i, 500.f), GetSceneTpye());
		}
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<GrayMira>(eColliderLayer::MONSTER, Vector2(100.f * i, 200.f), GetSceneTpye());
		}

		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<GreenMedusaHead>(eColliderLayer::MONSTER, Vector2(100.f * i, 0.0f), GetSceneTpye());
		}

		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<DurahanBoneKnight>(eColliderLayer::MONSTER, Vector2(100.f * i, -50.0f), GetSceneTpye());
		}

		//ya::object::Instantiate<Monster>(eColliderLayer::MONSTER, Vector2(200.f, 300.f));
		//ya::object::Instantiate<Monster>(eColliderLayer::MONSTER, Vector2(500.f, 300.f));
		//Ground* pG =  ya::object::Instantiate<Ground>(eColliderLayer::GROUND);
		//pG->SetPos({300.0f, 800.0f});

		Player* pPlayer = ya::object::Instantiate<Player>(eColliderLayer::PLAYER);
		CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		CollisionManager::SetLayer(eColliderLayer::MONSTER, eColliderLayer::PLAYER_PROJECTTILE, true);
		UIManager::Push(eUIType::HP);
		HUD* pHUD = static_cast<HUD*>(UIManager::GetUIInstance(eUIType::HP));
		assert(pHUD != nullptr);
		pHUD->SetPlayer(pPlayer);
		//Application::GetInstance().SetMenuBar(true);
		
#if 0
		ToolScene* toolScene = static_cast<ToolScene*>(SceneManager::GetSpecifiedScene(eSceneType::TOOL_SCENE));
		assert(toolScene != nullptr);
		toolScene->LoadTilePallete(L"Resources\\Tile\\Test");
#endif

	}
	void LogoScene::Tick()
	{
		//MeteoManager::GetInstance().Tick();
		// 오브젝트 Tick을 호출한다. 즉 나중에 호출되어야 함.
		Scene::Tick();
		if (IS_KEY_UP(eKeyCode::N))
		{
			SceneManager::ChangeSecne(eSceneType::TITLE_SCENE);
		}

	}
	void LogoScene::Render(HDC hdc)
	{
		//MeteoManager::GetInstance().Render(hdc);
		// 마찬가지
		//BitBlt(
		//	hdc,
		//	0,
		//	0,
		//	mpBGImage->GetWidth(),
		//	mpBGImage->GetHeight(),
		//	mpBGImage->GetDC(),
		//	0,
		//	0,
		//	SRCCOPY
		//);

		Scene::Render(hdc);

		wchar_t buffer[64];

		swprintf_s(buffer, 64, L"Logo Scene");
		size_t strLen = wcsnlen_s(buffer, 64);

		TextOut(hdc, 10, 30, buffer, static_cast<UINT>(strLen));
	}
	void LogoScene::Enter()
	{
		CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		CollisionManager::SetLayer(eColliderLayer::MONSTER, eColliderLayer::PLAYER_PROJECTTILE, true);
		CollisionManager::SetLayer(eColliderLayer::GROUND, eColliderLayer::PLAYER, true);
	}
	void LogoScene::Exit()
	{
		Scene::Exit();
	}
}
