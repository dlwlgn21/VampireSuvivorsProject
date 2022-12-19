#include "yaLevelBoxIcon.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	LevelBoxIcon::LevelBoxIcon()
		: HUD(eUIType::PLAY_PAUSED)
		, mType(eWeaponAndItemTypes::COUNT)
		, mCurrLevel(1)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"LevelBoxIcon1", L"Resources\\Image\\Icon\\LevelBoxIcon1.bmp");
		assert(mpImage != nullptr);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}
	void LevelBoxIcon::OnInitialize()
	{
	}
	void LevelBoxIcon::OnActive()
	{
	}
	void LevelBoxIcon::OnInactive()
	{
	}
	void LevelBoxIcon::OnTick()
	{
	}
	void LevelBoxIcon::OnRender(HDC hdc)
	{
		assert(mpImage != nullptr);

		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
			mImgWidth,
			mImgHeight,

			mpImage->GetDC(),
			0,
			0,
			mImgWidth,
			mImgHeight,
			mBlendFunc
		);
	}
	void LevelBoxIcon::OnUIClear()
	{
	}
	void LevelBoxIcon::IncreaseLevel()
	{
		++mCurrLevel;
		wchar_t key[32];
		wchar_t filePath[64];
		swprintf_s(key, 32, L"LevelBoxIcon%d", mCurrLevel);
		swprintf_s(filePath, 64, L"Resources\\Image\\Icon\\LevelBoxIcon%d.bmp", mCurrLevel);
		mpImage = Resources::Load<Image>(key, filePath);
		assert(mpImage != nullptr);
	}
}