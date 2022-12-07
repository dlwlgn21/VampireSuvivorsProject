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
		, mAnimCount(8)
		, mAnimDuration(ARROW_ANIM_DURATION)
		, mbIsUiPop(false)
	{
		assert(mpAnimImage != nullptr);
		assert(mpAnimator != nullptr);
		mbIsSelected = true;
		Vector2 noSelectedImgSize(305.0f, 95.0f);
		mPos = Vector2((SCREEN_WIDTH / 2) - (noSelectedImgSize.x / 2), SCREEN_HEIGHT / 2 + noSelectedImgSize.y);
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimSelected, mpAnimImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mAnimDuration, false);
		mpAnimator->CreateAnimation(mAnimNoSelected, mpImage, Vector2::ZERO, noSelectedImgSize, mAnimOffset, 1, mAnimDuration, false);
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