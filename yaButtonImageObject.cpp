#include "yaButtonImageObject.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	ButtonImageObject::ButtonImageObject(const std::wstring key)
		: GameObject()
		, mpImage(nullptr)
		, mKey(key)
	{
		if (mpImage == nullptr)
		{
			std::wstring path = L"Resources\\Image\\";
			path += key;
			mpImage = Resources::Load<Image>(mKey, path);
		}
		assert(mpImage != nullptr);
	}
	ButtonImageObject::~ButtonImageObject()
	{
	}
	void ButtonImageObject::Initialize()
	{
	}
	void ButtonImageObject::Tick()
	{
		GameObject::Tick();

	}
	void ButtonImageObject::Render(HDC hdc)
	{
		TransparentBlt(
			hdc,
			static_cast<int>(mPos.x),
			static_cast<int>(mPos.y),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			0, 0,
			mpImage->GetWidth(),
			mpImage->GetHeight(),
			RGB(255, 0, 255)
		);

		GameObject::Render(hdc);
	}
}