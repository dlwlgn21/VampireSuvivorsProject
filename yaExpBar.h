#pragma once
#include "yaHUD.h"

namespace ya
{
	class Image;
	class Player;
	class ExpBar final : public HUD
	{
	public:
		ExpBar();
		ExpBar(const ExpBar& other) = delete;
		ExpBar& operator=(const ExpBar& other) = delete;
		virtual ~ExpBar() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		__forceinline void SetPlayer(Player* pPlayer) { mpPlayer = pPlayer; }
	private:
		Image* mpExpAmountBarImage;
		Player* mpPlayer;
		int mImgWidth;
		int mImgHeight;
		int mAmountBarWidth;
		int mAmountBarHeight;
	};
}

