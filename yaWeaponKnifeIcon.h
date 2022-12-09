#pragma once
#include "yaHUD.h"

namespace ya
{
	class WeaponKnifeIcon final : public HUD
	{
	public:
		WeaponKnifeIcon();
		WeaponKnifeIcon(const WeaponKnifeIcon& other) = delete;
		WeaponKnifeIcon& operator=(const WeaponKnifeIcon& other) = delete;
		virtual ~WeaponKnifeIcon() = default;

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

