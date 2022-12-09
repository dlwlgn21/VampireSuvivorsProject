#pragma once
#include "yaHUD.h"

namespace ya 
{
	class Image;
	class PauseWeaponInfoBox final : public HUD
	{
	public:
		PauseWeaponInfoBox();
		PauseWeaponInfoBox(const PauseWeaponInfoBox& other) = delete;
		PauseWeaponInfoBox& operator=(const PauseWeaponInfoBox& other) = delete;
		virtual ~PauseWeaponInfoBox() = default;

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

