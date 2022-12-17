#include "yaLevelUpHUDMid.h"
#include "yaImage.h"
#include "yaPlayerLevelUpManager.h"

namespace ya
{
	LevelUpHUDMid::LevelUpHUDMid()
		: LevelUpHUD()
		, mImgWidth(0)
		, mImgHeight(0)
	{
	}
	void LevelUpHUDMid::OnInitialize()
	{
		mpImage = LevelUpUIManager::GetInstance().GetPickupedImage(eLevelUpUI::MID, mCurrType);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}
	void LevelUpHUDMid::OnActive()
	{
	}
	void LevelUpHUDMid::OnInactive()
	{
	}
	void LevelUpHUDMid::OnTick()
	{
	}
	void LevelUpHUDMid::OnRender(HDC hdc)
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
	void LevelUpHUDMid::OnUIClear()
	{
	}
}