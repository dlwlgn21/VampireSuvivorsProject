#pragma once
#include "yaUIBase.h"
namespace ya
{
	class Player;
	class HUD : public UIBase
	{
	public:
		HUD(eUIType type);
		virtual ~HUD();

		void OnInitialize() override;
		void OnActivate() override;
		void OnInActivate() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		inline void SetPlayer(Player* pPlayer) { mpPlayer = pPlayer; }
	private:
		BLENDFUNCTION mBlendFunc;
		Player* mpPlayer;

	};

}

