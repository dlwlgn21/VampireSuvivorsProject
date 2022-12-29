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
		void OnCollisionEnter(Collider* pCollider) override;
		void OnCollisionStay(Collider* pCollider) override;
		void OnCollisionExit(Collider* pCollider) override;

	private:
		Image* mpImage;
		Image* mpInvImage;
		Image* mpLeftDeathImage;
		Image* mpRightDeathImage;
		Animator* mpAnimator;
		Collider* mpCollider;

		const std::wstring mAnimMove;
		const std::wstring mAnimInvMove;
		const std::wstring mAnimLeftDeath;
		const std::wstring mAnimRightDeath;
		Vector2 mAnimMoveSize;
		Vector2 mAnimDeathSize;
		Vector2 mAnimOffset;
		UINT mAnimCount;
		float mAnimDuration;
		bool mbIsDeathFromWeapon;
		float mDeathAnimCounter;
	};

}

