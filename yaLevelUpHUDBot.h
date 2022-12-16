#pragma once
#include "yaHUD.h"

namespace ya
{
	class LevelUpHUDBot final : public HUD
	{
	public:
		LevelUpHUDBot();
		virtual ~LevelUpHUDBot() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
	private:
		int mImgWidth;
		int mImgHeight;
	};
}

