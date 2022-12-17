#pragma once
#include "yaPanel.h"

namespace ya
{
	class LevelUpArrow;
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

		void SetArrow(LevelUpArrow* pArrow);
	private:
		LevelUpArrow* mpArrow;
		int mImgWidth;
		int mImgHeight;
		const int M_TOP_POS;
		const int M_MID_POS;
		const int M_BOT_POS;
	};
}

