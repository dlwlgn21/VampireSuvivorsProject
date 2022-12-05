#pragma once
#include "yaHUD.h"

namespace ya 
{
	class CharacterIcon final : public HUD
	{
	public:
		CharacterIcon();
		CharacterIcon(const CharacterIcon& other) = delete;
		CharacterIcon& operator=(const CharacterIcon& other) = delete;
		virtual ~CharacterIcon() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
	};
}

