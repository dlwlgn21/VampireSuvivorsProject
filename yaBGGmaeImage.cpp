#include "yaBGGmaeImage.h"
#include "yaImage.h"
#include "yaCamera.h"
namespace ya
{
	BGGmaeImage::BGGmaeImage(const std::wstring& key, const std::wstring& path)
		: BGImageObject(key, path)
	{
		mPos = Vector2::ZERO;
		mScale = Vector2(2.0f, 2.0f);
	}
	void BGGmaeImage::Initialize()
	{
	}
	void BGGmaeImage::Tick()
	{
		GameObject::Tick();
	}
	void BGGmaeImage::Render(HDC hdc)
	{
		Vector2 pos = Camera::ToCameraPos(mPos);
		//TransparentBlt(
		//	hdc,
		//	static_cast<int>(pos.x - mImgWidth / 2.0f),
		//	static_cast<int>(pos.y - mImgHeigt / 2.0f),
		//	static_cast<int>(mImgWidth * mScale.x),
		//	static_cast<int>(mImgHeigt * mScale.y),

		//	mpImage->GetDC(),
		//	0,
		//	0,
		//	mImgWidth,
		//	mImgHeigt,
		//	RGB(255, 0, 255)
		//);

		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mImgWidth / 2.0f),
			static_cast<int>(pos.y - mImgHeigt / 2.0f),
			static_cast<int>(mImgWidth * mScale.x),
			static_cast<int>(mImgHeigt * mScale.y),

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