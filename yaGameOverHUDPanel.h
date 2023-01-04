#pragma once
#include "yaPanel.h"

namespace ya
{
	class GameOverHUDPanel final : public Panel
	{
	public:
		GameOverHUDPanel();
		GameOverHUDPanel(const GameOverHUDPanel& other) = delete;
		GameOverHUDPanel& operator=(const GameOverHUDPanel& other) = delete;
		virtual ~GameOverHUDPanel() = default;

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
		bool mbIsPopup;
	};
}

