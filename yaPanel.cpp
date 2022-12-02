#include "yaPanel.h"
#include "yaUIBase.h"
#include "yaImage.h"

namespace ya
{
	Panel::Panel(eUIType type)
		: UIBase(type)
	{
		mChilds.reserve(8);
		ZeroMemory(&mBlendFunc, sizeof(BLENDFUNCTION));
		mBlendFunc.BlendOp = AC_SRC_OVER;
		mBlendFunc.BlendFlags = 0;
		mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
		mBlendFunc.SourceConstantAlpha = 255;
	}

	void Panel::OnInitialize()
	{
	}

	void Panel::OnActive()
	{
	}

	void Panel::OnInactive()
	{
	}

	void Panel::OnTick()
	{
	}

	void Panel::OnRender(HDC hdc)
	{
		assert(mpImage != nullptr);

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
		mChilds.push_back(pUIBase);
	}

}