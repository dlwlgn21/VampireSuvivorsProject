#include "yaCharacterIcon.h"
#include "yaImage.h"

namespace ya
{
	CharacterIcon::CharacterIcon()
		: HUD(eUIType::CHARACTER_SELECTION)
	{
	}
	void CharacterIcon::OnInitialize()
	{
	}
	void CharacterIcon::OnActive()
	{
	}
	void CharacterIcon::OnInactive()
	{
	}
	void CharacterIcon::OnTick()
	{
	}
	void CharacterIcon::OnRender(HDC hdc)
	{
		assert(mpImage != nullptr);
		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			0,
			0,
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),
			mBlendFunc
		);
	}
	void CharacterIcon::OnUIClear()
	{
	}
}