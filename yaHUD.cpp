#include "yaHUD.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaPlayer.h"

namespace ya
{
	HUD::HUD(eUIType type)
		: UIBase(type)
		, mpPlayer(nullptr)
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
		assert(mpImage != nullptr);
		assert(mpPlayer != nullptr);

		float xRatio = mpPlayer->GetHp() / 100.0f;

		AlphaBlend(
			hdc,
			static_cast<int>(mPos.x),
			static_cast<int>(mPos.y),
			static_cast<int>(mpImage->GetWidth() * xRatio),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			0,
			0,
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),
			mBlendFunc
		);
	}

	void HUD::OnUIClear()
	{
	}
}