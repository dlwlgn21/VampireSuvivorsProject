#pragma once
#include "yaButtonImageObject.h"

namespace ya
{
	class Image;
	class Animator;
	class ExitButton final : public ButtonImageObject
	{
	public:
		ExitButton(const std::wstring& key, const std::wstring& path);

		virtual ~ExitButton() = default;
		ExitButton(const ExitButton& other) = delete;
		ExitButton& operator=(const ExitButton& other) = delete;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
		void ButtonClicked() override;

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

