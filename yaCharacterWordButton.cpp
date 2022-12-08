#include "yaCharacterWordButton.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaUIManager.h"

namespace ya
{
	CharacterWordButton::CharacterWordButton()
		: UIAnimObject(eUIType::CHARACTER_SELECTION)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"WordNoAnim", L"Resources\\Image\\CharacterSelectionNoSelected.bmp");
		assert(mpImage != nullptr);
		mpAnimImage = Resources::Load<Image>(L"WordAnim", L"Resources\\Image\\CharacterSelectionSelectedAnim.bmp");
		assert(mpAnimImage != nullptr);
		Create(mpAnimImage, Vector2(411.0f, 89.0f), Vector2(158.0f, 45.0f), 8, ARROW_ANIM_DURATION, false);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mAnimSize = Vector2(411.0f, 89.0f);
	}
	void CharacterWordButton::OnInitialize()
	{
		mbIsSelected = false;
	}
	void CharacterWordButton::OnActive()
	{
	}
	void CharacterWordButton::OnInactive()
	{
	}
	void CharacterWordButton::OnTick()
	{
		UIAnimObject::OnTick();
	}
	void CharacterWordButton::OnRender(HDC hdc)
	{
		if (mbIsSelected == false)
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
	void CharacterWordButton::OnUIClear()
	{
	}
	void CharacterWordButton::ButtonClicked()
	{
	}
}