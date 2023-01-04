#pragma once
#include "yaPanel.h"
namespace ya
{
	class GameOverTextHUD final : public Panel
	{
	public:
		GameOverTextHUD();
		GameOverTextHUD(const GameOverTextHUD& other) = delete;
		GameOverTextHUD& operator=(const GameOverTextHUD& other) = delete;
		virtual ~GameOverTextHUD() = default;

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

