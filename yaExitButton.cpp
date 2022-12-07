#include "yaExitButton.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaInput.h"

namespace ya
{
	ExitButton::ExitButton(const std::wstring& key, const std::wstring& path)
		: ButtonImageObject(key, path)
		, mpAnimImage(Resources::Load<Image>(L"ExitButtonAnim", L"Resources\\Image\\ExitButtonSelectedAnim.bmp"))
		, mpAnimator(new Animator())
		, mAnimSelected(L"ExitButtonAnim")
		, mAnimNoSelected(L"ExitButtonNoAnim")
		, mAnimSize(247.0f, 89.0f)
		, mAnimOffset(0.f, 40.f)
		, mAnimCount(8)
		, mAnimDuration(ARROW_ANIM_DURATION)
	{
		assert(mpAnimImage != nullptr);
		assert(mpAnimator != nullptr);
		Vector2 noSelectedImgSize(152.0f, 89.0f);
		mPos = Vector2(SCREEN_WIDTH / 2 - noSelectedImgSize.x * 2, BG_BLACK_BAR_Y_DIFF);
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimSelected, mpAnimImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mAnimDuration, false);
		mpAnimator->CreateAnimation(mAnimNoSelected, mpImage, Vector2::ZERO, noSelectedImgSize, mAnimOffset, 1, mAnimDuration, false);
		mpAnimator->PlayWithoutSpriteIdxReset(mAnimNoSelected, true);
	}
	void ExitButton::Initialize()
	{
	}
	void ExitButton::Tick()
	{
		GameObject::Tick();
		if (mbIsSelected)
			{ mpAnimator->PlayWithoutSpriteIdxReset(mAnimSelected, true); }
		else
			{ mpAnimator->PlayWithoutSpriteIdxReset(mAnimNoSelected, true); }
	}
	void ExitButton::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ExitButton::ButtonClicked()
	{
		OutputDebugStringA("\n\nExitButtonClicked!!!\n\n");
		PostQuitMessage(0);
	}
}