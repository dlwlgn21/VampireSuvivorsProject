#pragma once
#include "yaHUD.h"
#include "yaPlayerLevelUpManager.h"

namespace ya
{
	class LevelUpHUD : public HUD
	{
	public:
		LevelUpHUD();
		virtual ~LevelUpHUD() = default;

		virtual void OnInitialize() = 0;
		virtual void OnActive() = 0;
		virtual void OnInactive() = 0;
		virtual void OnTick() = 0;
		virtual void OnRender(HDC hdc) = 0;
		virtual void OnUIClear() = 0;

		__forceinline eWeaponAndItemTypes GetType() { return mCurrType; }
		__forceinline UINT GetCurrLevel() { return mCurrIdx; }

	protected:
		eWeaponAndItemTypes mCurrType;
		UINT mCurrIdx;
	};
}

