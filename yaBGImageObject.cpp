#include <cassert>
#include "yaBGImageObject.h"
#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	BGImageObject::BGImageObject(const std::wstring key)
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
	BGImageObject::~BGImageObject()
	{
	}
	void BGImageObject::Initialize()
	{
	}
	void BGImageObject::Tick()
	{
		GameObject::Tick();
	}
	void BGImageObject::Render(HDC hdc)
	{
		TransparentBlt(
			hdc,
			static_cast<int>(mPos.x + 160.0f),
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