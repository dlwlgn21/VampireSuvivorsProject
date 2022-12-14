#include "yaExpBar.h"
#include "yaPlayer.h"
#include "yaImage.h"
#include "yaResources.h"
namespace ya 
{
	ExpBar::ExpBar()
		: HUD(eUIType::PLAY_INFO_HUD)
		, mImgWidth(0)
		, mImgHeight(0)
		, mAmountBarWidth(0)
		, mAmountBarHeight(0)
		, mpPlayer(nullptr)
	{
		mpImage = Resources::Load<Image>(L"EXPBar", L"Resources\\Image\\EXPBar.bmp");
		assert(mpImage != nullptr);
		mpExpAmountBarImage = Resources::Load<Image>(L"EXPAmountBar", L"Resources\\Image\\EXPAmountBar.bmp");
		assert(mpExpAmountBarImage != nullptr);
		mPos = Vector2(static_cast<float>(BLACK_BAR_X_DIFF), 0.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mAmountBarWidth = mpExpAmountBarImage->GetWidth();
		mAmountBarHeight = mpExpAmountBarImage->GetHeight();
	}
	void ExpBar::OnInitialize()
	{
	}
	void ExpBar::OnActive()
	{
	}
	void ExpBar::OnInactive()
	{
	}
	void ExpBar::OnTick()
	{
	}
	void ExpBar::OnRender(HDC hdc)
	{
		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
			mImgWidth,
			mImgHeight,

			mpImage->GetDC(),
			0,
			0,
			mImgWidth,
			mImgHeight,
			mBlendFunc
		);

		assert(mpPlayer != nullptr);
		float xRatio = mpPlayer->GetExp() / 100.0f;
		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x + 9),
			static_cast<int>(mScreenPos.y + 9),
			static_cast<int>(mAmountBarWidth * xRatio),
			mAmountBarHeight,

			mpExpAmountBarImage->GetDC(),
			0,
			0,
			mAmountBarWidth,
			mAmountBarHeight,
			mBlendFunc
		);
	}
	void ExpBar::OnUIClear()
	{
	}
}