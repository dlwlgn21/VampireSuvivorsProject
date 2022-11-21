#include "yaFlyingSkull.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	FlyingSkull::FlyingSkull(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"FlyingSkull", L"Resources\\Image\\FlyingSkullAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"FlyingSkullInv", L"Resources\\Image\\FlyingSkullInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(30.0f, 45.0f)))
		, mAnimMove(L"FlyingSkullAnim")
		, mAnimInvMove(L"FlyingSkullAnimInv")
		, mAnimMoveSize(26.0f, 35.0f)
		, mAnimOffset(-8.f, -20.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"FlyingSkull");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void FlyingSkull::Tick()
	{
		GameObject::Tick();
	}
	void FlyingSkull::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void FlyingSkull::OnCollisionEnter(Collider* other)
	{
	}
	void FlyingSkull::OnCollisionStay(Collider* other)
	{
	}
	void FlyingSkull::OnCollisionExit(Collider* other)
	{
	}
}