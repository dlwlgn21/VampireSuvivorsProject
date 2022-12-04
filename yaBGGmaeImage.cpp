#include "yaBGGmaeImage.h"
#include "yaImage.h"

namespace ya
{
	BGGmaeImage::BGGmaeImage(const std::wstring& key, const std::wstring& path)
		: BGImageObject(key, path)
	{
		mPos = Vector2(160.0f, 0.0f);
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
		TransparentBlt(
			hdc,
			static_cast<int>(mPos.x),
			static_cast<int>(mPos.y),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			0,
			0,
			mpImage->GetWidth(),
			mpImage->GetHeight(),
			RGB(255, 0, 255)
		);
		GameObject::Render(hdc);
	}
}