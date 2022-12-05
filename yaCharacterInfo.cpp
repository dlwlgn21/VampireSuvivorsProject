#include "yaCharacterInfo.h"
#include "yaImage.h"

namespace ya
{
	CharacterInfo::CharacterInfo()
		: HUD(eUIType::CHARACTER_SELECTION)
	{
	}

	void CharacterInfo::OnInitialize()
	{
	}

	void CharacterInfo::OnActive()
	{
	}

	void CharacterInfo::OnInactive()
	{
	}

	void CharacterInfo::OnTick()
	{
	}

	void CharacterInfo::OnRender(HDC hdc)
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

	void CharacterInfo::OnUIClear()
	{
	}
}