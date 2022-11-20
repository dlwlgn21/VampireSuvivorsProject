#include "yaPanel.h"
#include "yaUIBase.h"
#include "yaImage.h"

namespace ya
{
	Panel::Panel(eUIType type)
		: UIBase(type)
	{
		ZeroMemory(&mBlendFunc, sizeof(BLENDFUNCTION));
		mBlendFunc.BlendOp = AC_SRC_OVER;
		mBlendFunc.BlendFlags = 0;
		mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
		mBlendFunc.SourceConstantAlpha = 255;
	}

	void Panel::OnInitialize()
	{
	}

	void Panel::OnActivate()
	{
	}

	void Panel::OnInActivate()
	{
	}

	void Panel::OnTick()
	{
	}

	void Panel::OnRender(HDC hdc)
	{
		if (mpImage == nullptr) { return; }
		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			static_cast<int>(0),
			static_cast<int>(0),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),
			mBlendFunc
		);
	}

	void Panel::OnUIClear()
	{
	}

	void Panel::AddUIBase(UIBase* pUIBase)
	{
	}

}