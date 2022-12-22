#define MAP_TOP_BOT_COLLIDER_WIDTH (4096.0f)
#define MAP_TOP_BOT_COLLIDER_HEIGHT (5.0f)

#include "yaBGGmaeImage.h"
#include "yaImage.h"
#include "yaCamera.h"
#include "yaObject.h"
#include "yaCollider.h"
#include "yaGameMapCollider.h"

namespace ya
{
	/*
		Collider* mpTopCollider;
		Collider* mpBotCollider;
		Collider* mpDeskCollider;
		Collider* mpPianoCollider;
	*/
	BGGmaeImage::BGGmaeImage(const std::wstring& key, const std::wstring& path)
		: BGImageObject(key, path)
	{
		mPos = Vector2::ZERO;
	}
	void BGGmaeImage::Initialize()
	{
		// Top
		instantiate(eMapColliderType::TOP, Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT), Vector2(0.0f, -460.0f));
		// Bot
		instantiate(eMapColliderType::BOT, Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT), Vector2(0.0f, 455.0f));
		// TopDesk
		instantiate(eMapColliderType::TOP_DESK, Vector2(165.0f, 50.0f), Vector2(-412.0f, -390.0f));
		// BotDesk
		instantiate(eMapColliderType::BOT_DESK, Vector2(100, 50.0f), Vector2(1340.0f, 310.0f));
		// PianoSideBook
		instantiate(eMapColliderType::PIANO_SIDE_BOOK, Vector2(380.f, 120.f), Vector2(-1410.0f, -130.f));
		// PianoMidBook
		instantiate(eMapColliderType::PIANO_MID_BOOK, Vector2(190.0f, 50.0f), Vector2(-1440.0f, -220.f));
		// Piano
		instantiate(eMapColliderType::PIANO, Vector2(126.0f, 30.0f), Vector2(-1437.0f, -50.f));
	}
	void BGGmaeImage::Tick()
	{
		GameObject::Tick();
	}
	void BGGmaeImage::Render(HDC hdc)
	{
		Vector2 pos = Camera::ToCameraPos(mPos);

		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mImgWidth / 2.0f),
			static_cast<int>(pos.y - mImgHeigt / 2.0f),
			static_cast<int>(mImgWidth),
			static_cast<int>(mImgHeigt),

			mpImage->GetDC(),
			0,
			0,
			mImgWidth,
			mImgHeigt,
			mBlendFunc
		);
		GameObject::Render(hdc);
	}
	void BGGmaeImage::instantiate(eMapColliderType type, Vector2 colliderSize, Vector2 colliderOffset)
	{
		GameMapCollider* gameObeject = new GameMapCollider(type, colliderSize, colliderOffset);
		Scene* scene = SceneManager::GetSpecifiedScene(eSceneType::PLAY_SCENE);
		scene->AddGameObject(static_cast<GameObject*>(gameObeject), eColliderLayer::BACKGROUND);
	}
}