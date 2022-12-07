#include "yaCharacterIcon.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	CharacterIcon::CharacterIcon()
		: SelectionMenuIcon(L"GennaroIconSelected", L"Resources\\Image\\GennaroIconSelected.bmp")
	{
		mpImage = Resources::Load<Image>(L"GennaroIcon", L"Resources\\Image\\GennaroChoiceBox.bmp");
		mpCurrRenderImage = mpImage;
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
	void CharacterIcon::OnUIClear()
	{
	}
}