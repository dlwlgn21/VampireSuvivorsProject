#include "yaOptionButton.h"
#include "yaImage.h"

namespace ya
{
	OptionButton::OptionButton(const std::wstring& key, const std::wstring& path)
		: ButtonImageObject(key, path)
	{
		mPos = Vector2(950.0f, BG_BLACK_BAR_Y_DIFF);

	}

	void OptionButton::Initialize()
	{
	}

	void OptionButton::Tick()
	{
		GameObject::Tick();
	}

	void OptionButton::Render(HDC hdc)
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
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),
			RGB(255, 0, 255)
		);
		GameObject::Render(hdc);
	}

}