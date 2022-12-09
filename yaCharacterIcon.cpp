#include "yaCharacterIcon.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	CharacterIcon::CharacterIcon()
		: SelectionMenuIcon(L"GennaroIconSelected", L"Resources\\Image\\GennaroIconSelected.bmp")
		, mOffset(11.0f, 11.0f)
		, mNoSelelctedImgWidth(0)
		, mNoSelelctedImgHeight(0)
		, mSelelctedImgWidth(0)
		, mSelelctedImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"GennaroIcon", L"Resources\\Image\\GennaroChoiceBox.bmp");
		mpCurrRenderImage = mpImage;
		mNoSelelctedImgWidth = mpImage->GetWidth();
		mNoSelelctedImgHeight = mpImage->GetHeight();
		mSelelctedImgWidth = mpSelectedImage->GetWidth();
		mSelelctedImgHeight = mpSelectedImage->GetHeight();
	}
	void CharacterIcon::OnInitialize()
	{
		mpCurrRenderImage = mpImage;
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

		if (mpCurrRenderImage == mpImage)
		{
			AlphaBlend(
				hdc,
				static_cast<int>(mScreenPos.x),
				static_cast<int>(mScreenPos.y),
				mNoSelelctedImgWidth,
				mNoSelelctedImgHeight,
			
				mpCurrRenderImage->GetDC(),
				0,
				0,
				mNoSelelctedImgWidth,
				mNoSelelctedImgHeight,
				mBlendFunc
			);
		}
		else
		{
			AlphaBlend(
				hdc,
				static_cast<int>(mScreenPos.x + mOffset.x),
				static_cast<int>(mScreenPos.y + mOffset.y),
				mSelelctedImgWidth,
				mSelelctedImgHeight,

				mpCurrRenderImage->GetDC(),
				0,
				0,
				mSelelctedImgWidth,
				mSelelctedImgHeight,
				mBlendFunc
			);
		}
	}
	void CharacterIcon::OnUIClear()
	{
	}
}