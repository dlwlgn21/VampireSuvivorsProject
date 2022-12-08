#pragma once
#include "yaUIAnimObject.h"

namespace ya
{
	class CharacterWordButton final : public UIAnimObject
	{
	public:
		CharacterWordButton();
		CharacterWordButton(const CharacterWordButton& other) = delete;
		CharacterWordButton& operator=(const CharacterWordButton& other) = delete;
		virtual ~CharacterWordButton() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
		void ButtonClicked() override;
	private:
		int mImgWidth;
		int mImgHeight;
	};
}

