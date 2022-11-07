#pragma once
#include "Common.h"
#include "yaComponent.h"

namespace ya
{
	class Image;
	class Animation;
	class Animator : public Component
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

		Animator();
		virtual ~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		Animation* FindAnimation(const std::wstring& name);
		void CreateAnimation(
			const std::wstring& name, Image* image, Vector2 leftTop,
			Vector2 size, Vector2 offset,
			UINT spriteLength, float duration,
			bool bIsAffectedCamera = true);
		void Play(const std::wstring& name, bool bIsLooping);

		//Event* GetEvents(const std::wstring key);

	public:
		Event mStartEvent;
		Event mCompleteEvent;
		Event mEndEvent;

	private:
		std::unordered_map<std::wstring, Animation*> mAnimations;
		//std::unordered_map<std::wstring, Event*> mEvents;
		Animation* mpCurrAnimation;
		bool mbIsLooping;
	};
}