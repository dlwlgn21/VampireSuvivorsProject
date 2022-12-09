#include "yaPauseWeaponInfoBox.h"
#include "yaWeaponKnifeIcon.h"
#include "yaPlayer.h"
#include "yaImage.h"
#include "yaResources.h"


namespace ya
{
	PauseWeaponInfoBox::PauseWeaponInfoBox()
		: HUD(eUIType::PLAY_PAUSED)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"WeaponInfoBox", L"Resources\\Image\\WeaponInfoBox.bmp");
		assert(mpImage != nullptr);
		mPos = Vector2(static_cast<float>(ACTUAL_GAME_SCREEN_X_DIFF) + 8.0f, 60.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mBlendFunc.SourceConstantAlpha = 128;
		WeaponKnifeIcon* pKnifeIcon = new WeaponKnifeIcon(mUIType);
		pKnifeIcon->SetPos(Vector2(mPos.x, 19.0f));
		AddUIChild(pKnifeIcon);
		
	}
	void PauseWeaponInfoBox::OnInitialize()
	{
	}
	void PauseWeaponInfoBox::OnActive()
	{
	}
	void PauseWeaponInfoBox::OnInactive()
	{
	}
	void PauseWeaponInfoBox::OnTick()
	{
	}
	void PauseWeaponInfoBox::OnRender(HDC hdc)
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
	void PauseWeaponInfoBox::OnUIClear()
	{
	}
}