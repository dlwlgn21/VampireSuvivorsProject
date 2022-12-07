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
		, mpSprtieSheet(nullptr)
	{
	}
	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			if (iter.second != nullptr) 
				{ delete iter.second; }
		}
		for (auto& iter : mEvents)
		{
			if (iter.second != nullptr) 
				{ delete iter.second; }
		}
	}

	void Animator::Tick()
	{
		if (mpCurrAnimation != nullptr)
		{
			mpCurrAnimation->Tick();
			if (mbIsLooping && mpCurrAnimation->IsComplete())
			{
				Animator::Events * events = FindEvents(mpCurrAnimation->GetName());
				if (events == nullptr)	
					{ assert(false); }
				else 
					{ events->mCompleteEvent(); }
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
		if (iter == mAnimations.end())	
			{ return nullptr; }
		return iter->second;
	}
	void Animator::CreateAnimation(const std::wstring& name, Image* image, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteCount, float duration, bool bIsAffectedCamera)
	{
		Animation* animation = FindAnimation(name);
		if (animation != nullptr)				{ assert(false); return; }

		animation = new Animation();
		animation->Create(image, leftTop, size, offset, spriteCount, duration, bIsAffectedCamera);
		animation->SetName(name);
		animation->SetAnimator(this);
		animation->SetScale(GetOwner()->GetScale());

		auto insertAnimRes = mAnimations.insert(std::make_pair(name, animation));
		if (insertAnimRes.second == false)		
		{ assert(false); return; }

		Events* events = new Events();
		auto insertEventsRes = mEvents.insert(std::make_pair(name, events));
		if (insertEventsRes.second == false)	
		{ assert(false); return; }
	}
	void Animator::Play(const std::wstring& name, bool bIsLooping)
	{
		Animator::Events* events = FindEvents(name);
		if (events == nullptr)					
		{ assert(false); }
		else									
		{ events->mStartEvent(); }
		
		Animation* pPrevAnim = mpCurrAnimation;
		mpCurrAnimation = FindAnimation(name);
		assert(mpCurrAnimation != nullptr);
		mpCurrAnimation->Reset();
		mbIsLooping = bIsLooping;
		if (pPrevAnim != mpCurrAnimation) 
		{ 
			if (events != nullptr)	
			{ 
				events->mEndEvent(); 
			}
		}
	}

	void Animator::PlayWithoutSpriteIdxReset(const std::wstring& name, bool bIsLooping)
	{
		Animator::Events* events = FindEvents(name);
		if (events == nullptr)
		{
			assert(false);
		}
		else
		{
			events->mStartEvent();
		}

		Animation* pPrevAnim = mpCurrAnimation;
		mpCurrAnimation = FindAnimation(name);
		assert(mpCurrAnimation != nullptr);
		mpCurrAnimation->ResetWithoutSpriteIdx();
		mbIsLooping = bIsLooping;
		if (pPrevAnim != mpCurrAnimation)
		{
			if (events != nullptr)
			{
				events->mEndEvent();
			}
		}
	}

	Animator::Events* Animator::FindEvents(const std::wstring& key)
	{
		auto iter = mEvents.find(key);

		if (iter == mEvents.end()) { return nullptr; }

		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& key)
	{
		Events* events = FindEvents(key);
		return events->mStartEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& key)
	{
		Events* events = FindEvents(key);
		return events->mEndEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& key)
	{
		Events* events = FindEvents(key);
		return events->mCompleteEvent.mEvent;;
	}

}