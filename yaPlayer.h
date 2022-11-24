#pragma once
#include "yaGameObejct.h"
#include "yaPlayerCustomAnimator.h"

namespace ya
{
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
		PlayerCustomAnimator* mpAnimator;
		Collider* mpCollider;

		Vector2 mAnimSize;
		Vector2 mAnimOffset;
		UINT mAnimCount;
		float mMinAnimInterval;
		Vector2 mColliderSize;

		Vector2 dir;

		int mHp;
		ePlayerDirection mEPlayerDir;
	};

}

