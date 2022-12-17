#include "yaLevelUpHUDTop.h"
#include "yaImage.h"
#include "yaPlayerLevelUpManager.h"

namespace ya
{
	LevelUpHUDTop::LevelUpHUDTop()
		: LevelUpHUD()
		, mImgWidth(0)
		, mImgHeight(0)
	{
	}

	void LevelUpHUDTop::OnInitialize()
	{
		mpImage = LevelUpUIManager::GetInstance().GetPickupedImage(eLevelUpUI::TOP, mCurrType);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}
	void LevelUpHUDTop::OnActive()
	{
	}
	void LevelUpHUDTop::OnInactive()
	{
	}
	void LevelUpHUDTop::OnTick()
	{
	}
	void LevelUpHUDTop::OnRender(HDC hdc)
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
	void LevelUpHUDTop::OnUIClear()
	{
	}
}