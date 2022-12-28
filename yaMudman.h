#pragma once
#include "yaMonster.h"

namespace ya
{
	class Image;
	class Animator;
	class Collider;
	class Player;
	class Mudman final : public Monster
	{
	public:
		Mudman(Vector2 pos, Player* pPlayer);
		virtual ~Mudman() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
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

