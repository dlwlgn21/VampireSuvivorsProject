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


	private:
		std::unordered_map<std::wstring, Animation*> mAnimations;
		Animation* mpCurrAnimation;
		bool mbIsLooping;

		Image* mpSprtieSheet;
	};
}