#include "yaTitleSceneOptionUIButton.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	TitleSceneOptionUIButton::TitleSceneOptionUIButton()
		: UIAnimObject(eUIType::START_MENU_SELECTION)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"OptionButtonNoAnim", L"Resources\\Image\\OptionButtonAlpha.bmp");
		assert(mpImage != nullptr);
		mpAnimImage = Resources::Load<Image>(L"OptionButtonAnim", L"Resources\\Image\\OptionButtonSelectedAnim.bmp");
		assert(mpAnimImage != nullptr);
		Create(mpAnimImage, Vector2(247.0f, 89.0f), Vector2(77.0f, 45.0f), 8, ARROW_ANIM_DURATION, false);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mAnimSize = Vector2(247.0f, 89.0f);
	}
	void TitleSceneOptionUIButton::OnInitialize()
	{
	}
	void TitleSceneOptionUIButton::OnActive()
	{
	}
	void TitleSceneOptionUIButton::OnInactive()
	{
	}
	void TitleSceneOptionUIButton::OnTick()
	{
		UIAnimObject::OnTick();
	}
	void TitleSceneOptionUIButton::OnRender(HDC hdc)
	{
		if (mbIsSelected)
		{
			Sprite& sprite = mSpriteSheet[mCurrSpriteIdx];
			Vector2 offset = sprite.Offset;
			AlphaBlend(
				hdc,
				static_cast<int>(mScreenPos.x + offset.x - sprite.Size.x / 2),
				static_cast<int>(mScreenPos.y + offset.y - sprite.Size.y / 2),
				static_cast<int>(sprite.Size.x),
				static_cast<int>(sprite.Size.y),

				mpAnimImage->GetDC(),
				static_cast<int>(sprite.LeftTop.x),
				static_cast<int>(sprite.LeftTop.y),
				static_cast<int>(sprite.Size.x),
				static_cast<int>(sprite.Size.y),
				mBlendFunc
			);
		}
		else
		{
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
	}
	void TitleSceneOptionUIButton::OnUIClear()
	{
	}
	void TitleSceneOptionUIButton::ButtonClicked()
	{
		char buffer[64];
		sprintf_s(buffer, 64, "\nOption Button Clicked!\n\n");
		OutputDebugStringA(buffer);
	}
}