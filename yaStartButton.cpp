#include "yaStartButton.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaUIManager.h"

namespace ya
{
	StartButton::StartButton(const std::wstring& key, const std::wstring& path)
		: ButtonImageObject(key, path)
		, mpAnimImage(Resources::Load<Image>(L"StartButtonAnim", L"Resources\\Image\\StartButtonAnim.bmp"))
		, mpAnimator(new Animator())
		, mAnimSelected(L"StartButtonAnim")
		, mAnimNoSelected(L"StartButtonNoAnim")
		, mAnimSize(399.0f, 95.0f)
		, mAnimOffset(140.0f, 60.0f)
		, mAnimCount(7)
		, mAnimDuration(0.2f)
	{
		assert(mpAnimImage != nullptr);
		assert(mpAnimator != nullptr);
		mbIsSelected = true;
		mPos = Vector2(1200/2 + 15.0f, 900/2 + 60.0f);
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimSelected, mpAnimImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mAnimDuration, false);
		mpAnimator->CreateAnimation(mAnimNoSelected, mpImage, Vector2::ZERO, Vector2(305.0f, 95.0f), mAnimOffset, 1, mAnimDuration, false);
		mpAnimator->Play(mAnimSelected, true);
	}
	void StartButton::Initialize()
	{
	}
	void StartButton::Tick()
	{
		GameObject::Tick();
		
		if (IS_KEY_DOWN(eKeyCode::Q) && !mbIsSelected)
		{
			UIManager::Push(eUIType::CHARACTER_SELECTION);
			mbIsSelected = true;
			mpAnimator->Play(mAnimSelected, true);
		}

		if (IS_KEY_DOWN(eKeyCode::R) && mbIsSelected)
		{
			UIManager::Pop(eUIType::CHARACTER_SELECTION);
			mbIsSelected = false;
		}

		if (IS_KEY_DOWN(eKeyCode::W) || IS_KEY_DOWN(eKeyCode::UP))
		{
			mbIsSelected = false;
			mpAnimator->Play(mAnimNoSelected, true);
		}
		else if (IS_KEY_DOWN(eKeyCode::S) || IS_KEY_DOWN(eKeyCode::DOWN))
		{
			mbIsSelected = true;
			mpAnimator->Play(mAnimSelected, true);
		}


	}
	void StartButton::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}