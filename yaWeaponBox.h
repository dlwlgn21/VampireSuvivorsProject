#pragma once
#include "yaHUD.h"

namespace ya
{
	class WeaponBox final : public HUD
	{
	public:
		WeaponBox(eUIType uiType);
		WeaponBox(const WeaponBox& other) = delete;
		WeaponBox& operator=(const WeaponBox& other) = delete;
		virtual ~WeaponBox() = default;

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

