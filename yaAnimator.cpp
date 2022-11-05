#include "yaAnimator.h"
#include "yaGameObejct.h"
#include "yaImage.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaAnimation.h"

namespace ya
{
	Animator::Animator()
		: Component(eComponentType::ANIMATOR)
		, mpCurrAnimation(nullptr)
		, mbIsLooping(false)
	{
	}
	Animator::~Animator()
	{
		for (auto iter : mAnimations)
		{
			if (iter.second != nullptr) { delete iter.second; }
		}
	}

	void Animator::Tick()
	{
		if (mpCurrAnimation != nullptr)
		{
			mpCurrAnimation->Tick();
			if (mbIsLooping && mpCurrAnimation->IsComplete())
			{
				mCompleteEvent();
				mpCurrAnimation->Reset();
			}
		}
	}
	void Animator::Render(HDC hdc)
	{
		if (mpCurrAnimation != nullptr) { mpCurrAnimation->Render(hdc); }
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end()) { return nullptr; }
		return iter->second;
	}
	void Animator::CreateAnimation(const std::wstring& name, Image* image, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration, bool bIsAffectedCamera)
	{
		Animation* animation = FindAnimation(name);
		if (animation != nullptr) { assert(false); return; }
		animation = new Animation();
		animation->Create(image, leftTop, size, offset, spriteLength, duration, bIsAffectedCamera);
		animation->SetName(name);
		animation->SetAnimator(this);
		animation->SetScale(GetOwner()->GetScale());
		mAnimations.insert(std::make_pair(name, animation));
	}
	void Animator::Play(const std::wstring& name, bool bIsLooping)
	{
		mStartEvent();
		Animation* pPrevAnim = mpCurrAnimation;
		mpCurrAnimation = FindAnimation(name);
		assert(mpCurrAnimation != nullptr);
		mpCurrAnimation->Reset();
		mbIsLooping = bIsLooping;
		if (pPrevAnim != mpCurrAnimation) { mEndEvent(); }
	}
}