#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaUIManager.h"

#include "yaBgImageObject.h"
#include "yaBoomGhost.h"
#include "yaBroomWitch.h"
#include "yaBlackBat.h"
#include "yaBossMira.h"
#include "yaBossBlackBat.h"
#include "yaBossNesparados.h"
#include "yaBossWitch.h"
#include "yaBossBroomWitch.h"
#include "yaBossMedusa.h"
#include "yaBossMudMan.h"
#include "yaBossMedusaHead.h"
#include "yaBossGreenGhost.h"
#include "yaBossLionHead.h"
#include "yaBossWhiteBat.h"


#include "yaDurahanBoneKnight.h"
#include "yaFlyingSkull.h"
#include "yaGreenGhost.h"
#include "yaGrayMira.h"
#include "yaMedusaHead.h"
#include "yaMudman.h"
#include "yaSkyColorGhost.h"
#include "yaLionHead.h"
#include "yaMagision.h"
#include "yaMiniHeadDurahan.h"
#include "yaMedusa.h"


#include "yaHUD.h"
#include "yaButton.h"
#include "yaPanel.h"

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
			ya::object::InstantiateAtAnotherScene<Mudman>(eColliderLayer::MONSTER, Vector2(100.f * i, 300.f), GetSceneTpye());
		}
#if 0
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
			ya::object::InstantiateAtAnotherScene<MedusaHead>(eColliderLayer::MONSTER, Vector2(100.f * i, 0.0f), GetSceneTpye());
		}

		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<DurahanBoneKnight>(eColliderLayer::MONSTER, Vector2(100.f * i, -50.0f), GetSceneTpye());
		}

		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<SkyColorGhost>(eColliderLayer::MONSTER, Vector2(100.f * i, -100.0f), GetSceneTpye());
		}

		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<LionHead>(eColliderLayer::MONSTER, Vector2(100.f * i, -150.0f), GetSceneTpye());
		}
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<Magision>(eColliderLayer::MONSTER, Vector2(100.f * i, -200.0f), GetSceneTpye());
		}

		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<MiniHeadDurahan>(eColliderLayer::MONSTER, Vector2(100.f * i, -250.0f), GetSceneTpye());
		}
		
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BroomWitch>(eColliderLayer::MONSTER, Vector2(100.f * i, -350.0f), GetSceneTpye());
		}
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BlackBat>(eColliderLayer::MONSTER, Vector2(100.f * i, -450.0f), GetSceneTpye());
		}		
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<FlyingSkull>(eColliderLayer::MONSTER, Vector2(100.f * i, -500.0f), GetSceneTpye());
		}		
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<Medusa>(eColliderLayer::MONSTER, Vector2(100.f * i, -600.0f), GetSceneTpye());
		}		
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossMira>(eColliderLayer::MONSTER, Vector2(100.f * i, -700.0f), GetSceneTpye());
		}		
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossBlackBat>(eColliderLayer::MONSTER, Vector2(100.f * i, -800.0f), GetSceneTpye());
		}		
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossNesparados>(eColliderLayer::MONSTER, Vector2(100.f * i, -900.0f), GetSceneTpye());
		}
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossWitch>(eColliderLayer::MONSTER, Vector2(100.f * i + 10, -1000.0f), GetSceneTpye());
		}		
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossBroomWitch>(eColliderLayer::MONSTER, Vector2(100.f * i + 30, -1200.0f), GetSceneTpye());
		}
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossMedusa>(eColliderLayer::MONSTER, Vector2(100.f * i + 30, -1400.0f), GetSceneTpye());
		}
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossMedusaHead>(eColliderLayer::MONSTER, Vector2(100.f * i + 30, -1600.0f), GetSceneTpye());
		}		
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossMudMan>(eColliderLayer::MONSTER, Vector2(100.f * i + 30, -1700.0f), GetSceneTpye());
		}
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossGreenGhost>(eColliderLayer::MONSTER, Vector2(100.f * i + 30, -1800.0f), GetSceneTpye());
		}
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossLionHead>(eColliderLayer::MONSTER, Vector2(100.f * i + 30, -1900.0f), GetSceneTpye());
		}		
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<BossWhiteBat>(eColliderLayer::MONSTER, Vector2(100.f * i + 30, -2000.0f), GetSceneTpye());
		}
#endif
	

		//ya::object::Instantiate<Monster>(eColliderLayer::MONSTER, Vector2(200.f, 300.f));
		//ya::object::Instantiate<Monster>(eColliderLayer::MONSTER, Vector2(500.f, 300.f));
		//Ground* pG =  ya::object::Instantiate<Ground>(eColliderLayer::GROUND);
		//pG->SetPos({300.0f, 800.0f});

		Player* pPlayer = ya::object::Instantiate<Player>(eColliderLayer::PLAYER);
		pPlayer->SetPos({ 300.0f, 200.0f });
		CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		CollisionManager::SetLayer(eColliderLayer::MONSTER, eColliderLayer::PLAYER_PROJECTTILE, true);


// FOR UI
#if 0
		UIManager::Push(eUIType::HP);
		UIManager::Push(eUIType::MP);
		UIManager::Push(eUIType::INVENTORY);
		HUD* pHUD = static_cast<HUD*>(UIManager::GetUIInstance(eUIType::MP));
		assert(pHUD != nullptr);
		pHUD->SetPlayer(pPlayer);
#endif
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
