#include "yaBGTitleImage.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BGTitleImage::BGTitleImage(const std::wstring& key, const std::wstring& path)
		: BGImageObject(key, path)
	{
		mPos = Vector2::ZERO;
	}
	void BGTitleImage::Initialize()
	{
	}
	void BGTitleImage::Tick()
	{
		GameObject::Tick();
	}
	void BGTitleImage::Render(HDC hdc)
	{
		TransparentBlt(
			hdc,
			static_cast<int>(mPos.x),
			static_cast<int>(mPos.y),
			static_cast<int>(mImgWidth * mScale.x),
			static_cast<int>(mImgHeigt * mScale.y),

			mpImage->GetDC(),
			0,
			0,
			mImgWidth,
			mImgHeigt,
			RGB(255, 0, 255)
		);

		//AlphaBlend(
		//	hdc,
		//	static_cast<int>(mPos.x),
		//	static_cast<int>(mPos.y),
		//	static_cast<int>(mImgWidth * mScale.x),
		//	static_cast<int>(mImgHeigt * mScale.y),

		//	mpImage->GetDC(),
		//	0,
		//	0,
		//	mImgWidth,
		//	mImgHeigt,
		//	mBlendFunc
		//);

		GameObject::Render(hdc);
	}
}