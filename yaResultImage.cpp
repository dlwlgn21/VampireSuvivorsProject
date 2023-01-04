#include "yaResultImage.h"
#include "yaImage.h"

namespace ya
{
	ResultImage::ResultImage(const std::wstring& key, const std::wstring& path)
		: BGImageObject(key, path)
	{
		mPos.x += ACTUAL_GAME_SCREEN_X_DIFF;
		mPos.y = 0.0f;
	}

	void ResultImage::Initialize()
	{
	}

	void ResultImage::Tick()
	{
		GameObject::Tick();
	}
	void ResultImage::Render(HDC hdc)
	{
		AlphaBlend(
			hdc,
			static_cast<int>(mPos.x),
			static_cast<int>(mPos.y),
			static_cast<int>(mImgWidth),
			static_cast<int>(mImgHeigt),

			mpImage->GetDC(),
			0,
			0,
			mImgWidth,
			mImgHeigt,
			mBlendFunc
		);
		GameObject::Render(hdc);
	}
}