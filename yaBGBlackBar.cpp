#include "yaBGBlackBar.h"
#include "yaImage.h"


namespace ya
{
	BGBlackBar::BGBlackBar(const std::wstring& key, const std::wstring& path)
		: BGImageObjectAlpha(key, path)
	{
		mPos = Vector2(BLACK_BAR_X_DIFF, 0.0f);
		mFunc.BlendOp = AC_SRC_OVER;
		mFunc.BlendFlags = 0;
		mFunc.AlphaFormat = AC_SRC_ALPHA;
		mFunc.SourceConstantAlpha = 128;
	}
	void BGBlackBar::Initialize()
	{
	}
	void BGBlackBar::Tick()
	{
		GameObject::Tick();
	}
	void BGBlackBar::Render(HDC hdc)
	{
		AlphaBlend(
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
			mFunc
		);

		GameObject::Render(hdc);
	}
}