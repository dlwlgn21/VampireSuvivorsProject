#include "yaWeaponKnifeIcon.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	WeaponKnifeIcon::WeaponKnifeIcon()
		: HUD(eUIType::PLAY_INFO_HUD)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"KnifeIcon", L"Resources\\Image\\KnifeIcon.bmp");
		assert(mpImage != nullptr);
		mPos = Vector2(-7.0f, 7.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}
	void WeaponKnifeIcon::OnInitialize()
	{
	}
	void WeaponKnifeIcon::OnActive()
	{
	}
	void WeaponKnifeIcon::OnInactive()
	{
	}
	void WeaponKnifeIcon::OnTick()
	{
	}
	void WeaponKnifeIcon::OnRender(HDC hdc)
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
	void WeaponKnifeIcon::OnUIClear()
	{
	}
}