#pragma once
#include "yaHUD.h"

namespace ya
{
	class PausePlayerStartInfoBox final : public HUD
	{
	public:
		PausePlayerStartInfoBox();
		PausePlayerStartInfoBox(const PausePlayerStartInfoBox& other) = delete;
		PausePlayerStartInfoBox& operator=(const PausePlayerStartInfoBox& other) = delete;
		virtual ~PausePlayerStartInfoBox() = default;

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

