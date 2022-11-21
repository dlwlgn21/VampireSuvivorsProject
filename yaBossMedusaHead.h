#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class Animator;
	class Collider;
	class BossMedusaHead : public GameObject
	{
	public:
		BossMedusaHead(Vector2 pos);
		virtual ~BossMedusaHead() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
		HPEN mPen;
		HBRUSH mBrush;
		Image* mpImage;
		Image* mpInvImage;
		Animator* mpAnimator;
		Collider* mpCollider;

		const std::wstring mAnimMove;
		const std::wstring mAnimInvMove;
		Vector2 mAnimMoveSize;
		Vector2 mAnimOffset;
		UINT mAnimCount;
		float mAnimDuration;
	};
}
