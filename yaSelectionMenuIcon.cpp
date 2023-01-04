#include "yaSelectionMenuIcon.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	SelectionMenuIcon::SelectionMenuIcon(const std::wstring& key, const std::wstring& path)
		: HUD(eUIType::CHARACTER_SELECTION)
		, mpSelectedImage(Resources::Load<Image>(key, path))
		, mpCurrRenderImage(nullptr)
	{
		assert(mpSelectedImage != nullptr);
		mBlendFunc.SourceConstantAlpha = 255;
	}
	void SelectionMenuIcon::ChangeRenderImage()
	{
		if (mpCurrRenderImage == mpImage)
			{ mpCurrRenderImage = mpSelectedImage; } 
		else
			{ mpCurrRenderImage = mpImage; }
	}
}

