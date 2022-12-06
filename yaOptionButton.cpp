#include "yaOptionButton.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaInput.h"
namespace ya
{
	OptionButton::OptionButton(const std::wstring& key, const std::wstring& path)
		: ButtonImageObject(key, path)
		, mpAnimImage(Resources::Load<Image>(L"OptionButtonAnim", L"Resources\\Image\\OptionButtonSelectedAnim.bmp"))
		, mpAnimator(new Animator())
		, mAnimSelected(L"OptionButtonAnim")
		, mAnimNoSelected(L"OptionButtonNoAnim")
		, mAnimSize(247.0f, 89.0f)
		, mAnimOffset(0.f, 40.f)
		, mAnimCount(7)
		, mAnimDuration(0.2f)
		, mbIsUpKeyDown(false)
	{
		assert(mpAnimImage != nullptr);
		assert(mpAnimator != nullptr);
		mPos = Vector2(1025.0f, BG_BLACK_BAR_Y_DIFF);
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimSelected, mpAnimImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mAnimDuration, false);
		mpAnimator->CreateAnimation(mAnimNoSelected, mpImage, Vector2::ZERO, Vector2(152.0f, 89.0f), mAnimOffset, 1, mAnimDuration, false);
		mpAnimator->Play(mAnimNoSelected, true);
	}

	void OptionButton::Initialize()
	{
	}

	void OptionButton::Tick()
	{
		GameObject::Tick();
		if (IS_KEY_DOWN(eKeyCode::W) || IS_KEY_DOWN(eKeyCode::UP))
		{
			if (!mbIsUpKeyDown)
			{
				mbIsUpKeyDown = true;
				mbIsSelected = true;
				mpAnimator->Play(mAnimSelected, true);
			}
		} 
		else if (IS_KEY_DOWN(eKeyCode::A) || IS_KEY_DOWN(eKeyCode::LEFT) && mbIsSelected && mbIsUpKeyDown)
		{
			mpAnimator->Play(mAnimNoSelected, true);
			mbIsSelected = false;
		} 
		else if ((IS_KEY_DOWN(eKeyCode::D) || IS_KEY_DOWN(eKeyCode::RIGHT) && !mbIsSelected) && mbIsUpKeyDown)
		{
			mpAnimator->Play(mAnimSelected, true);
			mbIsSelected = true;
		} 
		else if (IS_KEY_DOWN(eKeyCode::S) && mbIsSelected && mbIsUpKeyDown)
		{
			mpAnimator->Play(mAnimNoSelected, true);
			mbIsSelected = false;
			mbIsUpKeyDown = false;
		}
	}

	void OptionButton::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}