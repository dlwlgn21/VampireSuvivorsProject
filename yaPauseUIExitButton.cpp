#include "yaPauseUIExitButton.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaSceneManager.h"
#include "yaUIManager.h"

namespace ya
{
	PauseUIExitButton::PauseUIExitButton()
		: UIAnimObject(eUIType::START_MENU_SELECTION)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"ExitButtonNoAnim", L"Resources\\Image\\ExitButtonAlpha.bmp");
		assert(mpImage != nullptr);
		mpAnimImage = Resources::Load<Image>(L"ExitButtonAnim", L"Resources\\Image\\ExitButtonSelectedAnim.bmp");
		assert(mpAnimImage != nullptr);
		mAnimSize = Vector2(247.0f, 89.0f);
		Create(mpAnimImage, mAnimSize, Vector2(76.0f, 45.0f), 8, ARROW_ANIM_DURATION, false);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mPos = Vector2(SCREEN_WIDTH / 2.0f - mAnimSize.x / 2, SCREEN_HEIGHT / 2.0f - mAnimSize.y / 2 + 100.0f);
		mbIsSelected = false;
	}
	void PauseUIExitButton::OnInitialize()
	{
	}
	void PauseUIExitButton::OnActive()
	{
	}
	void PauseUIExitButton::OnInactive()
	{
	}
	void PauseUIExitButton::OnTick()
	{
		UIAnimObject::OnTick();
	}
	void PauseUIExitButton::OnRender(HDC hdc)
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
	void PauseUIExitButton::OnUIClear()
	{
	}
	void PauseUIExitButton::ButtonClicked()
	{
		UIManager::Pop(eUIType::PLAY_PAUSED);
		UIManager::Push(eUIType::START_MENU_SELECTION);
		SceneManager::ChangeSecne(eSceneType::TITLE_SCENE);
	}
}