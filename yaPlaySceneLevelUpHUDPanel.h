#pragma once
#include "yaPanel.h"

namespace ya
{
	class PlaySceneLevelUpHUDPanel final : public Panel
	{
	public:
		PlaySceneLevelUpHUDPanel();
		PlaySceneLevelUpHUDPanel(const PlaySceneLevelUpHUDPanel& other) = delete;
		PlaySceneLevelUpHUDPanel& operator=(const PlaySceneLevelUpHUDPanel& other) = delete;
		virtual ~PlaySceneLevelUpHUDPanel() = default;

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

