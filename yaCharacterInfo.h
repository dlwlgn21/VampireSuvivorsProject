#pragma once
#include "yaSelectionMenuIcon.h"

namespace ya
{
	class CharacterInfo final : public SelectionMenuIcon
	{
	public:
		CharacterInfo();
		CharacterInfo(const CharacterInfo& other) = delete;
		CharacterInfo& operator=(const CharacterInfo& other) = delete;
		virtual ~CharacterInfo() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
	};
}

