#pragma once
#include "yaButtonImageObject.h"

namespace ya
{
	class Animator;
	class StartButton final : public ButtonImageObject
	{
	public:
		StartButton(const std::wstring& key, const std::wstring& path);

		virtual ~StartButton() = default;
		StartButton(const StartButton& other) = delete;
		StartButton& operator=(const StartButton& other) = delete;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	private:
		Image* mpAnimImage;
		Animator* mpAnimator;

		const std::wstring mAnimSelected;
		const std::wstring mAnimNoSelected;
		Vector2 mAnimSize;
		Vector2 mAnimOffset;
		UINT mAnimCount;
		float mAnimDuration;
	};
}

