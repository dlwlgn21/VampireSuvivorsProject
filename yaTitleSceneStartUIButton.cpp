#include "yaTitleSceneStartUIButton.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaUIManager.h"

namespace ya
{
	TitleSceneStartUIButton::TitleSceneStartUIButton()
		: UIAnimObject(eUIType::START_MENU_SELECTION)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"StartButtonNoAnim", L"Resources\\Image\\StartButtonAlpha.bmp");
		assert(mpImage != nullptr);
		mpAnimImage = Resources::Load<Image>(L"StartButtonAnim", L"Resources\\Image\\StartButtonAnim.bmp");
		assert(mpAnimImage != nullptr);
		Create(mpAnimImage, Vector2(399.0f, 95.0f), Vector2::ZERO, 8, ARROW_ANIM_DURATION, false);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mAnimSize = Vector2(399.0f, 95.0f);
		mbIsSelected = true;
	}
	void TitleSceneStartUIButton::OnInitialize()
	{
	}
	void TitleSceneStartUIButton::OnActive()
	{
	}
	void TitleSceneStartUIButton::OnInactive()
	{
	}
	void TitleSceneStartUIButton::OnTick()
	{
		UIAnimObject::OnTick();
	}
	void TitleSceneStartUIButton::OnRender(HDC hdc)
	{
		if (mbIsSelected)
		{
			Sprite& sprite = mSpriteSheet[mCurrSpriteIdx];
			AlphaBlend(
				hdc,
				static_cast<int>(mScreenPos.x),
				static_cast<int>(mScreenPos.y),
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
	void TitleSceneStartUIButton::OnUIClear()
	{
	}
	void TitleSceneStartUIButton::ButtonClicked()
	{
		UIManager::Push(eUIType::CHARACTER_SELECTION);
	}
}