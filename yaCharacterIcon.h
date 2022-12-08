#pragma once
#include "yaSelectionMenuIcon.h"

namespace ya 
{
	class CharacterIcon final : public SelectionMenuIcon
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
	private:
		int mNoSelelctedImgWidth;
		int mNoSelelctedImgHeight;
		int mSelelctedImgWidth;
		int mSelelctedImgHeight;
		Vector2 mOffset;
	};
}

