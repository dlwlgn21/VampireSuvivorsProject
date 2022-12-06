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
		, mbIsUiPop(false)
	{
		assert(mpAnimImage != nullptr);
		assert(mpAnimator != nullptr);
		mbIsSelected = true;
		mPos = Vector2(1200/2 + 15.0f, 900/2 + 60.0f);
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimSelected, mpAnimImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mAnimDuration, false);
		mpAnimator->CreateAnimation(mAnimNoSelected, mpImage, Vector2::ZERO, Vector2(305.0f, 95.0f), mAnimOffset, 1, mAnimDuration, false);
		mpAnimator->PlayWithoutSpriteIdxReset(mAnimSelected, true);
	}
	void StartButton::Initialize()
	{
	}
	void StartButton::Tick()
	{
		GameObject::Tick();
		
		if (mbIsSelected)
			{ mpAnimator->PlayWithoutSpriteIdxReset(mAnimSelected, true); }
		else
			{ mpAnimator->PlayWithoutSpriteIdxReset(mAnimNoSelected, true); }

		if (IS_KEY_UP(eKeyCode::ESC) && mbIsSelected && mbIsUiPop)
		{
			UIManager::Pop(eUIType::CHARACTER_SELECTION);
			mbIsUiPop = false;
		}

	}
	void StartButton::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void StartButton::ButtonClicked()
	{
		if (mbIsUiPop)
		{
			return;
		}
		UIManager::Push(eUIType::CHARACTER_SELECTION);
		mbIsUiPop = true;
	}
}