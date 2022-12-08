#include "yaCharacterIcon.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	/*
		int mNoSelelctedImgWidth;
		int mNoSelelctedImgHeight;
		int mSelelctedImgWidth;
		int mSelelctedImgHeight;
	*/

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
				static_cast<int>(mNoSelelctedImgWidth),
				static_cast<int>(mNoSelelctedImgHeight),
			
				mpCurrRenderImage->GetDC(),
				0,
				0,
				static_cast<int>(mNoSelelctedImgWidth),
				static_cast<int>(mNoSelelctedImgHeight),
				mBlendFunc
			);
		}
		else
		{
			AlphaBlend(
				hdc,
				static_cast<int>(mScreenPos.x + mOffset.x),
				static_cast<int>(mScreenPos.y + mOffset.y),
				static_cast<int>(mSelelctedImgWidth),
				static_cast<int>(mSelelctedImgHeight),

				mpCurrRenderImage->GetDC(),
				0,
				0,
				static_cast<int>(mSelelctedImgWidth),
				static_cast<int>(mSelelctedImgHeight),
				mBlendFunc
			);
		}
	}
	void CharacterIcon::OnUIClear()
	{
	}
}