#include "yaStartButton.h"
#include "yaImage.h"

namespace ya
{
	StartButton::StartButton(const std::wstring& key, const std::wstring& path)
		: ButtonImageObject(key, path)
	{
		mPos = Vector2(1200/2, 900/2);
	}
	void StartButton::Initialize()
	{
	}
	void StartButton::Tick()
	{
		GameObject::Tick();
	}
	void StartButton::Render(HDC hdc)
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