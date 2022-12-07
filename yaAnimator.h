#pragma once
#include "Common.h"
#include "yaComponent.h"

namespace ya
{
	class Image;
	class Animation;
	class Animator final : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			// 함수처럼 사용하기 위해서 연산자 오버라이딩
			void operator()()
			{
				if (mEvent != nullptr) { mEvent(); }
			}
			std::function<void()> mEvent;
		};

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};
		Animator();
		virtual ~Animator();

		void Tick() override;
		void Render(HDC hdc) override;

		Animation* FindAnimation(const std::wstring& name);
		void CreateAnimation(
			const std::wstring& name, Image* image, Vector2 leftTop,
			Vector2 size, Vector2 offset,
			UINT spriteCount, float duration,
			bool bIsAffectedCamera = true);
		
		void Play(const std::wstring& name, bool bIsLooping);
		void PlayWithoutSpriteIdxReset(const std::wstring& name, bool bIsLooping);
		Events* FindEvents(const std::wstring& key);

		std::function<void()>& GetStartEvent(const std::wstring& key);
		std::function<void()>& GetEndEvent(const std::wstring& key);
		std::function<void()>& GetCompleteEvent(const std::wstring& key);

	private:
		std::unordered_map<std::wstring, Animation*> mAnimations;
		std::unordered_map<std::wstring, Events*> mEvents;
		Animation* mpCurrAnimation;
		bool mbIsLooping;

		Image* mpSprtieSheet;
	};
}