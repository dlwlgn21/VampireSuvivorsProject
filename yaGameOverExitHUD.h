#pragma once
#include "yaPanel.h"

namespace ya
{
	class GameOverExitHUD final : public Panel
	{
	public:
		GameOverExitHUD();
		GameOverExitHUD(const GameOverExitHUD& other) = delete;
		GameOverExitHUD& operator=(const GameOverExitHUD& other) = delete;
		virtual ~GameOverExitHUD() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
	private:
		int mImgWidth;
		int mImgHeight;
		int mTransparencyTimer;
	};
}