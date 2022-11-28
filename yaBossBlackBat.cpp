#include "yaBossBlackBat.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossBlackBat::BossBlackBat(Vector2 pos)
		: Monster(pos, 15)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BossBlackBat", L"Resources\\Image\\BossBlackBatAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BossBlackBatInv", L"Resources\\Image\\BossBlackBatInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(25.0f, 20.0f)))
		, mAnimMove(L"BossBlackBatAnim")
		, mAnimInvMove(L"BossBlackBatInvAnim")
		, mAnimMoveSize(25.0f, 23.0f)
		, mAnimOffset(-9.f, -10.f)
		, mAnimCount(3)
		, mAnimDuration(0.20f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BossBlackBat");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
	}

	void BossBlackBat::Tick()
	{
		GameObject::Tick();
	}
	void BossBlackBat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossBlackBat::OnCollisionEnter(Collider* other)
	{
	}
	void BossBlackBat::OnCollisionStay(Collider* other)
	{
	}
	void BossBlackBat::OnCollisionExit(Collider* other)
	{
	}
}