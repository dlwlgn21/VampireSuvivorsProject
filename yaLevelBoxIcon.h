#pragma once
#include "yaHUD.h"

namespace ya
{
	class LevelBoxIcon final : public HUD
	{
	public:
		LevelBoxIcon();
		virtual ~LevelBoxIcon() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		void IncreaseLevel();
		void SetType(const eWeaponAndItemTypes type) { mType = type; }
		eWeaponAndItemTypes GetType() const { return mType; }
	private:
		eWeaponAndItemTypes mType;
		UINT mCurrLevel;
		int mImgWidth;
		int mImgHeight;
	};
}

