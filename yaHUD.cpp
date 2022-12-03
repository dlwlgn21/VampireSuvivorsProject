#include "yaHUD.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaPlayer.h"

namespace ya
{
	HUD::HUD(eUIType type)
		: UIBase(type)
	{
		ZeroMemory(&mBlendFunc, sizeof(BLENDFUNCTION));
		mBlendFunc.BlendOp = AC_SRC_OVER;
		mBlendFunc.BlendFlags = 0;
		mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
		mBlendFunc.SourceConstantAlpha = 255;
	}

	void HUD::OnInitialize()
	{
	}
	void HUD::OnActive()
	{
	}
	void HUD::OnInactive()
	{

	}
	void HUD::OnTick()
	{
	}

	void HUD::OnRender(HDC hdc)
	{
	}

	void HUD::OnUIClear()
	{
	}
}