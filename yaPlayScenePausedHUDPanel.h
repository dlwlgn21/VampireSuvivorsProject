#pragma once
#include "yaPanel.h"

namespace ya
{
	enum class ePauseButton
	{
		CONTINUE,
		EXIT,
		COUNT
	};
	class Player;
	class UIAnimObject;
	class PlayScenePausedHUDPanel final : public Panel
	{
	public:
		PlayScenePausedHUDPanel();
		PlayScenePausedHUDPanel(const PlayScenePausedHUDPanel& other) = delete;
		PlayScenePausedHUDPanel& operator=(const PlayScenePausedHUDPanel& other) = delete;
		virtual ~PlayScenePausedHUDPanel() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		void SetButtonPtrs();
	private:
		UIAnimObject* mpButtons[static_cast<UINT>(ePauseButton::COUNT)];
		int mImgWidth;
		int mImgHeight;
	};
}

