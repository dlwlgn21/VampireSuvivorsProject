#include "yaCharacterInfo.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	CharacterInfo::CharacterInfo()
		: SelectionMenuIcon(L"GennaroIconInfoSelected", L"Resources\\Image\\GennaroIconInfoSelected.bmp")
	{
		mpImage = Resources::Load<Image>(L"GennaroInfo", L"Resources\\Image\\GennaroInfo.bmp");
		mpCurrRenderImage = mpImage;
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
		assert(mpCurrRenderImage != nullptr);
		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
			static_cast<int>(mpCurrRenderImage->GetWidth()),
			static_cast<int>(mpCurrRenderImage->GetHeight()),

			mpCurrRenderImage->GetDC(),
			0,
			0,
			static_cast<int>(mpCurrRenderImage->GetWidth()),
			static_cast<int>(mpCurrRenderImage->GetHeight()),
			mBlendFunc
		);
	}

	void CharacterInfo::OnUIClear()
	{
	}
}