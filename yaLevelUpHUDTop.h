#pragma once
#include "yaHUD.h"
#include "yaPlayerLevelUpManager.h"

namespace ya
{
	class LevelUpHUDTop final : public HUD
	{
	public:
		LevelUpHUDTop();
		virtual ~LevelUpHUDTop() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
	private:
		eWeaponAndItemTypes mCurrShowingType;
		UINT mCurrShowingIdx;
		int mImgWidth;
		int mImgHeight;
	};
}

