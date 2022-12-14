#pragma once
#include "yaPanel.h"

namespace ya
{
	class Player;
	class PlaySceneHUDPanel final : public Panel
	{
	public:
		PlaySceneHUDPanel();
		PlaySceneHUDPanel(const PlaySceneHUDPanel& other) = delete;
		PlaySceneHUDPanel& operator=(const PlaySceneHUDPanel& other) = delete;
		virtual ~PlaySceneHUDPanel() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		void SetPlayerToHpBar(Player* pPlayer);
		void SetPlayerToExpBar(Player* pPlayer);
	};
}


