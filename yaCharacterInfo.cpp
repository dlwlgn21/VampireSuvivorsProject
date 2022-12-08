#include "yaCharacterInfo.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	CharacterInfo::CharacterInfo()
		: SelectionMenuIcon(L"GennaroIconInfoSelected", L"Resources\\Image\\GennaroIconInfoSelected.bmp")
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"GennaroInfo", L"Resources\\Image\\GennaroInfo.bmp");
		assert(mpImage != nullptr);
		mpCurrRenderImage = mpImage;
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}

	void CharacterInfo::OnInitialize()
	{
		mpCurrRenderImage = mpImage;
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
			static_cast<int>(mImgWidth),
			static_cast<int>(mImgHeight),

			mpCurrRenderImage->GetDC(),
			0,
			0,
			static_cast<int>(mImgWidth),
			static_cast<int>(mImgHeight),
			mBlendFunc
		);
	}

	void CharacterInfo::OnUIClear()
	{
	}
}