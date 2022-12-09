#include "yaStageLibraryIcon.h"
#include "yaImage.h"
#include "yaResources.h"
namespace ya
{
	StageLibraryIcon::StageLibraryIcon()
		: SelectionMenuIcon(L"StageLibrarySelected", L"Resources\\Image\\StageSelectionIcon.bmp")
		, mOffset(2.0f, 2.0f)
		, mNoSelelctedImgWidth(0)
		, mNoSelelctedImgHeight(0)
		, mSelelctedImgWidth(0)
		, mSelelctedImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"StageLibraryNoSelected", L"Resources\\Image\\StageNoSelectionIcon.bmp");
		assert(mpImage != nullptr);
		mpCurrRenderImage = mpImage;
		mNoSelelctedImgWidth = mpImage->GetWidth();
		mNoSelelctedImgHeight = mpImage->GetHeight();
		mSelelctedImgWidth = mpSelectedImage->GetWidth();
		mSelelctedImgHeight = mpSelectedImage->GetHeight();
		mbIsFullScreen = true;
	}
	void StageLibraryIcon::OnInitialize()
	{
		mpCurrRenderImage = mpImage;
	}
	void StageLibraryIcon::OnActive()
	{
	}
	void StageLibraryIcon::OnInactive()
	{
	}
	void StageLibraryIcon::OnTick()
	{
	}
	void StageLibraryIcon::OnRender(HDC hdc)
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
	void StageLibraryIcon::OnUIClear()
	{
	}
}