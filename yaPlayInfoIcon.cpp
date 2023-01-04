#include "yaPlayInfoIcon.h"
#include "yaImage.h"
#include "yaResources.h"
namespace ya
{
	PlayInfoIcon::PlayInfoIcon(eUIType eUiType, ePlayInfoIconPos ePos, eWeaponAndItemTypes eItemType, Vector2 pos)
		: HUD(eUiType)
		, meIconPos(ePos)
		, meType(eItemType)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		switch (eItemType)
		{
		case eWeaponAndItemTypes::KNIFE:
			mpImage = Resources::Load<Image>(L"KnifeIcon", L"Resources\\Image\\Icon\\KnifeIcon.bmp");
			break;
		case eWeaponAndItemTypes::FIRE_WAND:
			mpImage = Resources::Load<Image>(L"FireWandIocn", L"Resources\\Image\\Icon\\FireWandIcon.bmp");
			break;
		case eWeaponAndItemTypes::RUNE:
			mpImage = Resources::Load<Image>(L"RuneIcon", L"Resources\\Image\\Icon\\RuneIcon.bmp");
			break;
		case eWeaponAndItemTypes::AXE:
			mpImage = Resources::Load<Image>(L"AxeIcon", L"Resources\\Image\\Icon\\AxeIcon.bmp");
			break;
		case eWeaponAndItemTypes::WEAPON_SPEED:
			mpImage = Resources::Load<Image>(L"WeaponSpeedIcon", L"Resources\\Image\\Icon\\WeaponSpeedIcon.bmp");
			break;
		case eWeaponAndItemTypes::WEAPON_DAMAGE:
			mpImage = Resources::Load<Image>(L"WeaponDamageIcon", L"Resources\\Image\\Icon\\WeaponDamageIcon.bmp");
			break;
		case eWeaponAndItemTypes::MOVE_SPEED:
			mpImage = Resources::Load<Image>(L"MoveSpeedIcon", L"Resources\\Image\\Icon\\MoveSpeed.bmp");
			break;
		case eWeaponAndItemTypes::PLAYER_AMOUR:
			mpImage = Resources::Load<Image>(L"AmourIcon", L"Resources\\Image\\Icon\\AmourIcon.bmp");
			break;
		default:
			assert(false);
			break;
		}
		assert(mpImage != nullptr);
		mPos = pos;
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
	}
	void PlayInfoIcon::OnInitialize()
	{
		mBlendFunc.SourceConstantAlpha = 255;
	}
	void PlayInfoIcon::OnActive()
	{
	}
	void PlayInfoIcon::OnInactive()
	{
	}
	void PlayInfoIcon::OnTick()
	{
	}
	void PlayInfoIcon::OnRender(HDC hdc)
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
	void PlayInfoIcon::OnUIClear()
	{
	}
}