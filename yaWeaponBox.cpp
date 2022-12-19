#include "yaWeaponBox.h"
#include "yaWeaponKnifeIcon.h"
#include "yaPlayer.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaPlayInfoIcon.h"

namespace ya
{
	WeaponBox::WeaponBox(eUIType uiType)
		: HUD(uiType)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"WeaponPanel", L"Resources\\Image\\WeaponPanel.bmp");
		assert(mpImage != nullptr);
		mPos = Vector2(static_cast<float>(BLACK_BAR_X_DIFF) + 8.0f, 60.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mBlendFunc.SourceConstantAlpha = 128;
		//PlayInfoIcon* pKnifeIcon = new PlayInfoIcon(ePlayInfoIconPos::TOP, eWeaponAndItemTypes::KNIFE, Vector2(-7.0f, 7.0f));
		//AddUIChild(pKnifeIcon);
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