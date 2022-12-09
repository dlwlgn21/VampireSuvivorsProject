#pragma once
#include "yaPanel.h"

namespace ya
{
	class StageSelectionPanel final : public Panel
	{
	public:
		StageSelectionPanel();
		StageSelectionPanel(const StageSelectionPanel& other) = delete;
		StageSelectionPanel& operator=(const StageSelectionPanel& other) = delete;
		virtual ~StageSelectionPanel() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
	private:
		bool mbIsFirstEntered;
		int mImgWidth;
		int mImgHeight;
	};
}

