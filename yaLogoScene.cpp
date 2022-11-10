#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaObject.h"
#include "yaApplication.h"

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
		ya::object::Instantiate<Player>(eColliderLayer::PLAYER);
		ya::object::Instantiate<Monster>(eColliderLayer::MONSTER, Vector2(200.f, 300.f));
		ya::object::Instantiate<Monster>(eColliderLayer::MONSTER, Vector2(500.f, 300.f));
		CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		CollisionManager::SetLayer(eColliderLayer::MONSTER, eColliderLayer::PLAYER_PROJECTTILE, true);
		Application::GetInstance().SetMenuBar(true);
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
		Scene::Enter();
		CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		CollisionManager::SetLayer(eColliderLayer::MONSTER, eColliderLayer::PLAYER_PROJECTTILE, true);
	}
	void LogoScene::Exit()
	{
		Scene::Exit();
	}
}
