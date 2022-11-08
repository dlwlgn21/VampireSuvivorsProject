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
			const std::wstring& name, Image* image, Vector2 leftTop,
			Vector2 size, Vector2 offset,
			UINT spriteLength, float duration);

	private:
		float mSpeed;
		HPEN mPen;
		HBRUSH mBrush;
		Image* mpIdleImage;
		Image* mpMoveImage;
		Image* mpMoveInvImage;
		Animator* mpAnimator;

		const std::wstring mAnimIdle;
		const std::wstring mAnimMove;
		const std::wstring mAnimMoveInv;
		Vector2 mAnimIdleSize;
		Vector2 mAnimMoveSize;
		Vector2 mAnimOffset;
		UINT mAnimCount;
		float mAnimDuration;
		float mAnimRowInterval;
		Vector2 mColliderScale;

		Vector2 dir;
	};

}

