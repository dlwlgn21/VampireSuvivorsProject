#pragma once
#include "yaPanel.h"

namespace ya
{
	class CharacterSelectionPanel final : public Panel
	{
	public:
		CharacterSelectionPanel(eUIType type);
		CharacterSelectionPanel(const CharacterSelectionPanel& other) = delete;
		CharacterSelectionPanel& operator=(const CharacterSelectionPanel& other) = delete;
		virtual ~CharacterSelectionPanel() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
	};

}

