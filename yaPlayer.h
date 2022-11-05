#pragma once
#include "yaGameObejct.h"
#include "yaAnimator.h"

namespace ya
{
	class Image;
	class Animator;

	class Player final : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void WalkComplete();

	private:
		void createAnimation(
			const std::wstring& name, Vector2 leftTop,
			Vector2 size, Vector2 offset,
			UINT spriteLength, float duration);

	private:
		float mSpeed;
		HPEN mPen;
		HBRUSH mBrush;
		Image* mpImage;
		Animator* mpAnimator;

		const std::wstring mAnimIdle;
		const std::wstring mAnimMoveUp;
		const std::wstring mAnimMoveDown;
		const std::wstring mAnimMoveLeft;
		const std::wstring mAnimMoveRight;
		Vector2 mAnimSize;
		float animDuration;
		float mAnimRowInterval;

	};

}

