#include "yaHealthBar.h"
#include "yaPlayer.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	HealthBar::HealthBar()
		: HUD(eUIType::PLAY_INFO_HUD)
		, mpPlayer(nullptr)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"HPBar", L"Resources\\Image\\HPBar.bmp");
		assert(mpImage != nullptr);
		mPos = Vector2(SCREEN_WIDTH / 2 - 42.0f, SCREEN_HEIGHT / 2 + 43.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}
	void HealthBar::OnInitialize()
	{
	}
	void HealthBar::OnActive()
	{
	}
	void HealthBar::OnInactive()
	{
	}
	void HealthBar::OnTick()
	{
	}
	void HealthBar::OnRender(HDC hdc)
	{
		assert(mpImage != nullptr);
		assert(mpPlayer != nullptr);

		float xRatio = mpPlayer->GetHp() / 100.0f;

		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
			static_cast<int>(mImgWidth * xRatio),
			mImgHeight,

			mpImage->GetDC(),
			0,
			0,
			mImgWidth,
			mImgHeight,
			mBlendFunc
		);
	}
	void HealthBar::OnUIClear()
	{
	}
}