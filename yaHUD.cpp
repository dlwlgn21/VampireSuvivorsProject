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
	HUD::~HUD()
	{
	}
	void HUD::OnInitialize()
	{
	}
	void HUD::OnActivate()
	{
	}
	void HUD::OnInActivate()
	{

	}
	void HUD::OnTick()
	{
	}

	void HUD::OnRender(HDC hdc)
	{
		if (mpImage == nullptr) { return; }
		if (mpPlayer == nullptr) { return; }

		float xRatio = mpPlayer->GetHp() / 100.0f;

		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
			static_cast<int>(mpImage->GetWidth() * xRatio),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			static_cast<int>(0),
			static_cast<int>(0),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),
			mBlendFunc
		);
	}

	void HUD::OnUIClear()
	{
	}
}