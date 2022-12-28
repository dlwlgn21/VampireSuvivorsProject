#include "yaMudman.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"
#include "yaPlayer.h"
#include "yaTime.h"

namespace ya
{
	Mudman::Mudman(Vector2 pos, Player* pPlayer)
		: Monster(pos, pPlayer, MUDMAN_INITIAL_HP, MUDMAN_INITIAL_DAMAGE, ONE_MIN_NORMAL_MONSTER_EXP, 200.0f)
		, mpImage(Resources::Load<Image>(L"Mudman", L"Resources\\Image\\MudmanAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"MudmanInv", L"Resources\\Image\\MudmanInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(25.0f, 40.0f)))
		, mAnimMove(L"MudmanAnim")
		, mAnimInvMove(L"MudmanAnimInv")
		, mAnimMoveSize(56.0f, 66.0f)
		, mAnimOffset(0.0f, 0.0f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"Mudman");
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpCollider->SetColliderLayer(eColliderLayer::MONSTER);
		mpAnimator->CreateAnimation(mAnimMove,	mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void Mudman::Tick()
	{
		GameObject::Tick();

		SetVelocity();

		mPos.x -= mVelocityX * Time::DeltaTime();
		mPos.y -= mVelocityY * Time::DeltaTime();
	}
	void Mudman::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void Mudman::OnCollisionStay(Collider* other)
	{

	}
	void Mudman::OnCollisionExit(Collider* other)
	{

	}
}