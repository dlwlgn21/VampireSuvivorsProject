#pragma once
#include "yaHUD.h"

namespace ya
{
	class Player;
	class HealthBar final : public HUD
	{
	public:
		HealthBar();
		virtual ~HealthBar() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		__forceinline void SetPlayer(Player* pPlayer) { mpPlayer = pPlayer; }
	private:
		Player* mpPlayer;

	};

}

