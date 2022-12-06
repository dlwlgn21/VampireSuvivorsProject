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
		, mAnimCount(7)
		, mAnimDuration(0.2f)
		, mbIsUpKeyDown(false)
	{
		assert(mpAnimImage != nullptr);
		assert(mpAnimator != nullptr);
		mPos = Vector2(480.0f, BG_BLACK_BAR_Y_DIFF);
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimSelected, mpAnimImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mAnimDuration, false);
		mpAnimator->CreateAnimation(mAnimNoSelected, mpImage, Vector2::ZERO, Vector2(152.0f, 89.0f), mAnimOffset, 1, mAnimDuration, false);
		mpAnimator->Play(mAnimNoSelected, true);
	}
	void ExitButton::Initialize()
	{
	}
	void ExitButton::Tick()
	{
		GameObject::Tick();
		if (IS_KEY_DOWN(eKeyCode::W) || IS_KEY_DOWN(eKeyCode::UP) && !mbIsSelected)
		{
			mbIsUpKeyDown = true;
		}

		if (IS_KEY_DOWN(eKeyCode::A) && !mbIsSelected && mbIsUpKeyDown)
		{
			mpAnimator->Play(mAnimSelected, true);
			mbIsSelected = true;
		}
		else if (IS_KEY_DOWN(eKeyCode::D) && mbIsSelected && mbIsUpKeyDown)
		{
			mpAnimator->Play(mAnimNoSelected, true);
			mbIsSelected = false;
		}
		else if (IS_KEY_DOWN(eKeyCode::S) && mbIsSelected)
		{
			mpAnimator->Play(mAnimNoSelected, true);
			mbIsSelected = false;
			mbIsUpKeyDown = false;
		}
	}
	void ExitButton::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}