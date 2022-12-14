#pragma once
#include "yaLevelUpHUD.h"

namespace ya
{
	class LevelUpHUDMid final : public LevelUpHUD
	{
	public:
		LevelUpHUDMid();
		virtual ~LevelUpHUDMid() = default;

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

