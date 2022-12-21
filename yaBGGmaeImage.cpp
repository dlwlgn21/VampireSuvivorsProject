#define MAP_TOP_BOT_COLLIDER_WIDTH (4096.0f)
#define MAP_TOP_BOT_COLLIDER_HEIGHT (5.0f)

#include "yaBGGmaeImage.h"
#include "yaImage.h"
#include "yaCamera.h"

//#include "yaCollider.h"

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
		//, mpTopCollider(new Collider(Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT)))
		//, mpBotCollider(new Collider(Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT)))
		//, mpTopDeskCollider(new Collider(Vector2(165.0f, 50.0f)))
		//, mpBotDeskCollider(new Collider(Vector2(100, 50.0f)))
		//, mpPianoSideBookCollider(new Collider(Vector2(380.f, 120.f)))
		//, mpPianoMidBookCollider(new Collider(Vector2(190.0f, 64.0f)))
		//, mpPianoCollider(new Collider(Vector2(126.0f, 50.0f)))
	{
		//assert(
		//	mpTopCollider != nullptr && 
		//	mpBotCollider != nullptr && 
		//	mpTopDeskCollider != nullptr && 
		//	mpBotDeskCollider != nullptr &&
		//	mpPianoSideBookCollider != nullptr && 
		//	mpPianoMidBookCollider != nullptr && 
		//	mpPianoCollider != nullptr
		//);

		mPos = Vector2::ZERO;
		//AddComponent(mpTopCollider);
		//AddComponent(mpBotCollider);
		//AddComponent(mpTopDeskCollider);
		//AddComponent(mpBotDeskCollider);
		//AddComponent(mpPianoSideBookCollider);
		//AddComponent(mpPianoMidBookCollider);
		//AddComponent(mpPianoCollider);

		//mpTopCollider->SetOffset(Vector2(0.0f, -500.0f));
		//mpBotCollider->SetOffset(Vector2(0.0f, 455.0f));
		//mpTopDeskCollider->SetOffset(Vector2(-412.0f, -390.0f));
		//mpBotDeskCollider->SetOffset(Vector2(1340.0f, 310.0f));
		//mpPianoSideBookCollider->SetOffset(Vector2(-1410.0f, -130.f));
		//mpPianoMidBookCollider->SetOffset(Vector2(-1440.0f, -220.f));
		//mpPianoCollider->SetOffset(Vector2(-1437.0f, -60.f));
	}
	void BGGmaeImage::Initialize()
	{
	}
	void BGGmaeImage::Tick()
	{
		GameObject::Tick();
	}
	void BGGmaeImage::Render(HDC hdc)
	{
		Vector2 pos = Camera::ToCameraPos(mPos);
		//TransparentBlt(
		//	hdc,
		//	static_cast<int>(pos.x - mImgWidth / 2.0f),
		//	static_cast<int>(pos.y - mImgHeigt / 2.0f),
		//	static_cast<int>(mImgWidth * mScale.x),
		//	static_cast<int>(mImgHeigt * mScale.y),

		//	mpImage->GetDC(),
		//	0,
		//	0,
		//	mImgWidth,
		//	mImgHeigt,
		//	RGB(255, 0, 255)
		//);

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
}