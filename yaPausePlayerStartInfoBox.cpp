#include "yaPausePlayerStartInfoBox.h"
#include "yaPlayer.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	PausePlayerStartInfoBox::PausePlayerStartInfoBox()
		: HUD(eUIType::PLAY_PAUSED)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"PlayerInfoStatBox", L"Resources\\Image\\PlayerStatInfo.bmp");
		assert(mpImage != nullptr);
		mPos = Vector2(static_cast<float>(ACTUAL_GAME_SCREEN_X_DIFF) + 8.0f, 200.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mBlendFunc.SourceConstantAlpha = 128;
	}
	void PausePlayerStartInfoBox::OnInitialize()
	{
	}
	void PausePlayerStartInfoBox::OnActive()
	{
	}
	void PausePlayerStartInfoBox::OnInactive()
	{
	}
	void PausePlayerStartInfoBox::OnTick()
	{
	}
	void PausePlayerStartInfoBox::OnRender(HDC hdc)
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
	void PausePlayerStartInfoBox::OnUIClear()
	{
	}
}