#include <cassert>
#include "yaBGImageObjectAlpha.h"
#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	BGImageObjectAlpha::BGImageObjectAlpha(const std::wstring key)
		: GameObject()
		, mpImage(nullptr)
		, mKey(key)
	{
		std::wstring path = L"Resources\\Image\\";
		path += key;
		mpImage = Resources::Load<Image>(mKey, path);
		assert(mpImage != nullptr);
		mFunc.BlendOp = AC_SRC_OVER;
		mFunc.BlendFlags = 0;
		mFunc.AlphaFormat = AC_SRC_ALPHA;
		mFunc.SourceConstantAlpha = 128;
	}
	BGImageObjectAlpha::~BGImageObjectAlpha()
	{
	}
	void BGImageObjectAlpha::Initialize()
	{
	}
	void BGImageObjectAlpha::Tick()
	{
		GameObject::Tick();
	}
	void BGImageObjectAlpha::Render(HDC hdc)
	{
		AlphaBlend(
			hdc,
			static_cast<int>(mPos.x),
			static_cast<int>(mPos.y),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			0, 0,
			mpImage->GetWidth(),
			mpImage->GetHeight(),
			mFunc
		);
		GameObject::Render(hdc);
	}
}