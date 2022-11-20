#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class Animator;
	class BossNesparados : public GameObject
	{
	public:
		BossNesparados(Vector2 pos);
		virtual ~BossNesparados() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
		HPEN mPen;
		HBRUSH mBrush;
		Image* mpImage;
		Animator* mpAnimator;

		const std::wstring mAnimMove;
		Vector2 mAnimMoveSize;
		Vector2 mAnimOffset;
		UINT mAnimCount;
		float mAnimDuration;
	};

}

