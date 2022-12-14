#include "yaWeaponBox.h"
#include "yaWeaponKnifeIcon.h"
#include "yaPlayer.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	WeaponBox::WeaponBox()
		: HUD(eUIType::PLAY_INFO_HUD)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"WeaponPanel", L"Resources\\Image\\WeaponPanel.bmp");
		assert(mpImage != nullptr);
		mPos = Vector2(static_cast<float>(BLACK_BAR_X_DIFF) + 8.0f, 60.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mBlendFunc.SourceConstantAlpha = 128;
		WeaponKnifeIcon* pKnifeIcon = new WeaponKnifeIcon(mUIType);
		AddUIChild(pKnifeIcon);
	}
	void WeaponBox::OnInitialize()
	{
	}
	void WeaponBox::OnActive()
	{
	}
	void WeaponBox::OnInactive()
	{
	}
	void WeaponBox::OnTick()
	{
	}
	void WeaponBox::OnRender(HDC hdc)
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
	}
	void WeaponBox::OnUIClear()
	{
	}


}