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
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"FlyingSkullAnim")
		, mAnimMoveSize(26.0f, 35.0f)
		, mAnimOffset(-8.f, -20.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		SetName(L"FlyingSkull");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"FlyingSkull", L"Resources\\Image\\FlyingSkullAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(30.0f, 45.0f)));
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