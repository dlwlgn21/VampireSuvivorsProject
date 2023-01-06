#include "yaKillCountIcon.h"
#include "yaImage.h"

namespace ya
{
	KillCountIcon::KillCountIcon(const std::wstring& key, const std::wstring& path)
		: BGImageObject(key, path)
	{
		mPos.x = 1580.0f;
		mPos.y = 65.0f;
	}
	void KillCountIcon::Initialize()
	{
		//BGImageObject::Initialize();
	}
	void KillCountIcon::Tick()
	{
		//BGImageObject::Tick();
	}
	void KillCountIcon::Render(HDC hdc)
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