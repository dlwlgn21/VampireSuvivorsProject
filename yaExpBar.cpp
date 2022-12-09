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
	{
		mpImage = Resources::Load<Image>(L"EXPBar", L"Resources\\Image\\EXPBar.bmp");
		assert(mpImage != nullptr);
		mPos = Vector2(static_cast<float>(BLACK_BAR_X_DIFF), 0.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
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
		assert(mpImage != nullptr);

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
	}
	void ExpBar::OnUIClear()
	{
	}
}