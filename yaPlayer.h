#pragma once
#include "yaGameObejct.h"
#include "yaPlayerCustomAnimator.h"

namespace ya
{
	enum class ePlayerLookDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UP_LEFT,
		UP_RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT,
		COUNT
	};
	class Image;
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
		float mSpeed;
		HPEN mPen;
		HBRUSH mBrush;
		Image* mpLeftImage;
		Image* mpRightImage;
		Image* mpLeftHittedImage;
		Image* mpRightHittedImage;
		PlayerCustomAnimator* mpAnimator;
		Collider* mpCollider;

		Vector2 mAnimSize;
		Vector2 mAnimOffset;
		UINT mAnimCount;
		float mMinAnimInterval;

		Vector2 dir;

		int mHp;
		ePlayerAnimState mePlayerAnimState;
		ePlayerLookDirection meLookDir;
		float KnifeShootInterval;
		float KnifeTimer;
	};

}

