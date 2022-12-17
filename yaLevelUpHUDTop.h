#pragma once
#include "yaLevelUpHUD.h"

namespace ya
{
	class LevelUpHUDTop final : public LevelUpHUD
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
		int mImgWidth;
		int mImgHeight;
	};
}

