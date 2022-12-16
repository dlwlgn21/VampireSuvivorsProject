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
		mpImage = LevelUpUIManager::GetInstance().GetImage(eWeaponAndItemTypes::MOVE_SPEED, 0);
		assert(mpImage != nullptr);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}
	void LevelUpHUDBot::OnInitialize()
	{
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