#include "yaBGGoldCount.h"
#include "yaImage.h"


namespace ya
{
	BGGoldCount::BGGoldCount(const std::wstring& key, const std::wstring& path)
		: BGImageObject(key, path)
	{
		mPos = Vector2(1200 / 2 + 15.0f, BG_BLACK_BAR_Y_DIFF);
	}
	void BGGoldCount::Initialize()
	{
	}
	void BGGoldCount::Tick()
	{
		GameObject::Tick();
	}
	void BGGoldCount::Render(HDC hdc)
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