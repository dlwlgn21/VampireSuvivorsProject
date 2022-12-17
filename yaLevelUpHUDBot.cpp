#include "yaLevelUpHUDBot.h"
#include "yaImage.h"
#include "yaPlayerLevelUpManager.h"

namespace ya
{
	LevelUpHUDBot::LevelUpHUDBot()
		: HUD(eUIType::PLAY_LEVEL_UP)
		, mImgWidth(0)
		, mImgHeight(0)
	{
	}
	void LevelUpHUDBot::OnInitialize()
	{
		mpImage = LevelUpUIManager::GetInstance().GetPickupedImage(eLevelUpUI::BOT);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}
	void LevelUpHUDBot::OnActive()
	{
	}
	void LevelUpHUDBot::OnInactive()
	{
	}
	void LevelUpHUDBot::OnTick()
	{
	}
	void LevelUpHUDBot::OnRender(HDC hdc)
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
	void LevelUpHUDBot::OnUIClear()
	{
	}
}