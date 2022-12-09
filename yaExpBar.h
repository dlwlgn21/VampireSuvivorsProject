#pragma once
#include "yaHUD.h"

namespace ya
{
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
	private:
		int mImgWidth;
		int mImgHeight;
	};
}

