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
}