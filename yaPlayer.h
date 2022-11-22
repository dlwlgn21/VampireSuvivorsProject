#pragma once
#include "yaGameObejct.h"
#include "yaAnimator.h"

namespace ya
{
	class Image;
	class Animator;
	class Collider;
	class Player final : public GameObject
	{
	public:
		Player();
		virtual ~Player() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void WalkComplete();

		inline void SetHp(int hp) { mHp = hp; }
		inline int GetHp() { return mHp; }

	private:
		void createAnimation(
			const std::wstring& name, Image* image, Vector2 leftTop,
			Vector2 size, Vector2 offset,
			UINT spriteCount, float duration);

	private:
		float mSpeed;
		HPEN mPen;
		HBRUSH mBrush;
		Image* mpIdleImage;
		Image* mpMoveImage;
		Image* mpMoveInvImage;
		Animator* mpAnimator;
		Collider* mpCollider;

		const std::wstring mAnimMove;
		const std::wstring mAnimMoveInv;
		Vector2 mAnimMoveSize;
		Vector2 mAnimOffset;
		UINT mAnimCount;
		float mAnimDuration;
		float mAnimRowInterval;
		Vector2 mColliderScale;

		Vector2 dir;

		int mHp;
	};

}

