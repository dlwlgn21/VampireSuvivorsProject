#include "yaPauseUIContinueButton.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaUIManager.h"

namespace ya
{
	PauseUIContinueButton::PauseUIContinueButton()
		: UIAnimObject(eUIType::PLAY_PAUSED)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"PauseContinueButton", L"Resources\\Image\\ContinueButton.bmp");
		assert(mpImage != nullptr);
		mpAnimImage = Resources::Load<Image>(L"PauseContinueButtonAnim", L"Resources\\Image\\ContinueButtonAnim.bmp");
		assert(mpAnimImage != nullptr);
		mAnimSize = Vector2(398.0f, 95.0f);
		Create(mpAnimImage, mAnimSize, Vector2(152.0f, 47.0f), 8, ARROW_ANIM_DURATION, false);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mbIsSelected = true;
		mPos = Vector2(SCREEN_WIDTH / 2.0f - mAnimSize.x / 2, SCREEN_HEIGHT / 2.0f - mAnimSize.y / 2);
	}
	void PauseUIContinueButton::OnInitialize()
	{
	}
	void PauseUIContinueButton::OnActive()
	{
	}
	void PauseUIContinueButton::OnInactive()
	{
	}
	void PauseUIContinueButton::OnTick()
	{
		UIAnimObject::OnTick();
	}
	void PauseUIContinueButton::OnRender(HDC hdc)
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
	void PauseUIContinueButton::OnUIClear()
	{
	}
	void PauseUIContinueButton::ButtonClicked()
	{
		UIManager::Pop(eUIType::PLAY_PAUSED);
		UIManager::Push(eUIType::PLAY_INFO_HUD);
	}
}