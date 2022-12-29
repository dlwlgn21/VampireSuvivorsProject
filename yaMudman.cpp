#include "yaMudman.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"
#include "yaPlayer.h"
#include "yaTime.h"
#include "yaWeapon.h"

namespace ya
{
	Mudman::Mudman(Vector2 pos, Player* pPlayer)
		: Monster(pos, pPlayer, MUDMAN_INITIAL_HP, MUDMAN_INITIAL_DAMAGE, ONE_MIN_NORMAL_MONSTER_EXP, 200.0f)
		, mpImage(Resources::Load<Image>(L"Mudman", L"Resources\\Image\\MudmanAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"MudmanInv", L"Resources\\Image\\MudmanInvAnim.bmp"))
		, mpLeftDeathImage(Resources::Load<Image>(L"MudmanLDeath", L"Resources\\Image\\MudManLeftDeathAnim.bmp"))
		, mpRightDeathImage(Resources::Load<Image>(L"MudmanRDeath", L"Resources\\Image\\MudManDeathRightAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(25.0f, 40.0f)))
		, mAnimMove(L"MudmanAnim")
		, mAnimInvMove(L"MudmanAnimInv")
		, mAnimLeftDeath(L"MudmanAnimLDeath")
		, mAnimRightDeath(L"MudmanAnimRDeath")
		, mAnimMoveSize(56.0f, 66.0f)
		, mAnimDeathSize(56.0f, 56.0f)
		, mAnimOffset(0.0f, 0.0f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
		, mDeathAnimCounter(mAnimDuration * 7)
		, mbIsDeathFromWeapon(false)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpLeftDeathImage != nullptr);
		assert(mpRightDeathImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"Mudman");
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpCollider->SetColliderLayer(eColliderLayer::MONSTER);
		mpAnimator->CreateAnimation(mAnimMove,	mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimLeftDeath, mpLeftDeathImage, Vector2::ZERO, mAnimDeathSize, mAnimOffset, 7, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimRightDeath, mpRightDeathImage, Vector2::ZERO, mAnimDeathSize, mAnimOffset, 7, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void Mudman::Tick()
	{
		if (mbIsDeathFromWeapon)
		{
			mDeathAnimCounter -= Time::DeltaTime();
			//if (std::abs(mDeathAnimCounter) <= FLT_EPSILON)
			//{
			//	mbIsActive = false;
			//}
			if (mDeathAnimCounter <= 0.0f)
			{
				mbIsActive = false;
			}
		}
		//Vector2 monDir = GetVectorToPlayer();
		//monDir.Normalize();

		//mPos.x += monDir.x * mSpeed * Time::DeltaTime();
		//mPos.y += monDir.y * mSpeed * Time::DeltaTime();
		Monster::Tick();
	}
	void Mudman::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Mudman::OnCollisionEnter(Collider* pCollider)
	{
		switch (pCollider->GetColliderLayer())
		{
		case eColliderLayer::PLAYER_PROJECTTILE:
		{
			Weapon* pWeapon = static_cast<Weapon*>(pCollider->GetOwner());
			mHP -= pWeapon->GetDamage();
			if (mHP <= 0)
			{
				mbIsDeathFromWeapon = true;
				assert(mpPlayer != nullptr);
				mpPlayer->IncreaseExp(mExp);
				mpAnimator->Play(mAnimRightDeath, false);
			}
			break;
		}
		default:
			break;
		}
	}
	void Mudman::OnCollisionStay(Collider* pCollider)
	{
	}
	void Mudman::OnCollisionExit(Collider* pCollider)
	{
	}
}