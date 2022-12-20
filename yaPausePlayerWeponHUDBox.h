#pragma once
#include "yaHUD.h"

namespace ya
{
	class PausePlayerWeponHUDBox final : public HUD
	{
	public:
		PausePlayerWeponHUDBox();
		PausePlayerWeponHUDBox(const PausePlayerWeponHUDBox& other) = delete;
		PausePlayerWeponHUDBox& operator=(const PausePlayerWeponHUDBox& other) = delete;
		virtual ~PausePlayerWeponHUDBox() = default;

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

