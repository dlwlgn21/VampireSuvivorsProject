#define MAP_TOP_BOT_COLLIDER_WIDTH (4096.0f)
#define MAP_TOP_BOT_COLLIDER_HEIGHT (5.0f)

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
#include "yaTime.h"
#include "yaApplication.h"
#include "yaBGGmaeImage.h"
#include "yaGameMapCollider.h"



namespace ya
{
	PlayScene::PlayScene()
		: mSceneType(eSceneType::PLAY_SCENE)
		, mpPlayer(nullptr)
		, mbUiFlag(true)
		, mHwnd(Application::GetInstance().GetWindowData().hwnd)
	{
		mFont.lfHeight = 30;
		mFont.lfWidth = 0;
		mFont.lfEscapement = 0;
		mFont.lfOrientation = 0;
		mFont.lfItalic = 0;
		mFont.lfUnderline = 0;
		mFont.lfStrikeOut = 0;
		mFont.lfCharSet = ARABIC_CHARSET;
		mFont.lfOutPrecision = 0;
		mFont.lfClipPrecision = 0;
		mFont.lfQuality = 0;
		mFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		lstrcpy(mFont.lfFaceName, L"Tekton Pro");
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		mpPlayer = ya::object::Instantiate<Player>(eColliderLayer::PLAYER);
		BGGmaeImage* bgGameImage = ya::object::InstantiateAtAnotherScene<BGGmaeImage>(eColliderLayer::BACKGROUND, L"BGGmaeMap", L"Resources\\Image\\MapTwo.bmp", GetSceneTpye());
		bgGameImage->Initialize();

		int monsterCount = 15;
		for (int i = 0; i < monsterCount; ++i)
		{
			ya::object::InstantiateAtAnotherScene<Mudman>(eColliderLayer::MONSTER, Vector2(100.0f * i, 300.f), mpPlayer, GetSceneTpye());
		}
		setColliderLayer();
	}
	void PlayScene::Tick()
	{
		Scene::Tick();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t buffer[64];
		swprintf_s(buffer, 64, L"%d : %d", static_cast<int>(Time::TotalTime() / 60), static_cast<int>(Time::TotalTime()) % 60);
		int len = lstrlenW(buffer);

		HFONT hFont = CreateFontIndirect(&mFont);
		HFONT hOldFont;
		hOldFont = (HFONT)SelectObject(hdc, hFont);

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOutW(hdc, SCREEN_WIDTH / 2 - 25, 60, buffer, len);

		SelectObject(hdc, hOldFont);
		DeleteObject(hFont);
		ReleaseDC(mHwnd, hdc);

	}
	void PlayScene::Enter()
	{
		Scene::Enter();
		Time::StartTimeCounting();
		setColliderLayer();
		PlaySceneHUDPanel* pPanel = static_cast<PlaySceneHUDPanel*>(UIManager::GetUIInstanceOrNull(eUIType::PLAY_INFO_HUD));
		assert(pPanel != nullptr);
		pPanel->SetPlayerToHpBar(mpPlayer);
		pPanel->SetPlayerToExpBar(mpPlayer);
	}

	void PlayScene::Exit()
	{
		Scene::Exit();
		Time::Reset();
	}
	void PlayScene::setColliderLayer()
	{
		CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::BACKGROUND, true);
		CollisionManager::SetLayer(eColliderLayer::PLAYER, eColliderLayer::MONSTER, true);
		CollisionManager::SetLayer(eColliderLayer::MONSTER, eColliderLayer::PLAYER_PROJECTTILE, true);
		CollisionManager::SetLayer(eColliderLayer::BACKGROUND, eColliderLayer::PLAYER_PROJECTTILE, true);
	}
}