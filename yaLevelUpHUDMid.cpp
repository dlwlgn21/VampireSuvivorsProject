#include "yaLevelUpHUDMid.h"
#include "yaImage.h"
#include "yaPlayerLevelUpManager.h"

namespace ya
{
	LevelUpHUDMid::LevelUpHUDMid()
		: HUD(eUIType::PLAY_LEVEL_UP)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = LevelUpUIManager::GetInstance().mpImages[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)][0];
		assert(mpImage != nullptr);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}
	void LevelUpHUDMid::OnInitialize()
	{
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