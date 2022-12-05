#include "yaCharacterSelectionPanel.h"
#include "yaImage.h"

namespace ya
{

	CharacterSelectionPanel::CharacterSelectionPanel(eUIType type)
		: Panel(eUIType::CHARACTER_SELECTION)
	{
	}
	void CharacterSelectionPanel::OnInitialize()
	{
	}
	void CharacterSelectionPanel::OnActive()
	{
	}
	void CharacterSelectionPanel::OnInactive()
	{
	}
	void CharacterSelectionPanel::OnTick()
	{
	}
	void CharacterSelectionPanel::OnRender(HDC hdc)
	{
		assert(mpImage != nullptr);

		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			static_cast<int>(0),
			static_cast<int>(0),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),
			mBlendFunc
		);
	}
	void CharacterSelectionPanel::OnUIClear()
	{
	}
}