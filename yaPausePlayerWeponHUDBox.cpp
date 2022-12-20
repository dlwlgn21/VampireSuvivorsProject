#include "yaPausePlayerWeponHUDBox.h"
#include "yaPlayer.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	PausePlayerWeponHUDBox::PausePlayerWeponHUDBox()
		: HUD(eUIType::PLAY_PAUSED)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"PlayerInfoWeaponHUDBox", L"Resources\\Image\\WeaponInfoBox.bmp");
		assert(mpImage != nullptr);
		mPos = Vector2(static_cast<float>(ACTUAL_GAME_SCREEN_X_DIFF) + 8.0f, 50.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mBlendFunc.SourceConstantAlpha = 128;
	}
	void PausePlayerWeponHUDBox::OnInitialize()
	{
	}
	void PausePlayerWeponHUDBox::OnActive()
	{
	}
	void PausePlayerWeponHUDBox::OnInactive()
	{
	}
	void PausePlayerWeponHUDBox::OnTick()
	{
	}
	void PausePlayerWeponHUDBox::OnRender(HDC hdc)
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
	void PausePlayerWeponHUDBox::OnUIClear()
	{
	}
}