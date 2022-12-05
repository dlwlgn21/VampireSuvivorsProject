#include "yaHealthBar.h"
#include "yaPlayer.h"
#include "yaImage.h"

namespace ya
{
	HealthBar::HealthBar()
		: HUD(eUIType::PLAY_INFO_HUD)
		, mpPlayer(nullptr)
	{
	}
	void HealthBar::OnInitialize()
	{
	}
	void HealthBar::OnActive()
	{
	}
	void HealthBar::OnInactive()
	{
	}
	void HealthBar::OnTick()
	{
	}
	void HealthBar::OnRender(HDC hdc)
	{
		assert(mpImage != nullptr);
		assert(mpPlayer != nullptr);

		float xRatio = mpPlayer->GetHp() / 100.0f;

		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
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
	void HealthBar::OnUIClear()
	{
	}
}