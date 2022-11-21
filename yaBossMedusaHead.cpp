#include "yaBossMedusaHead.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossMedusaHead::BossMedusaHead(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BossMedusaHead", L"Resources\\Image\\BossMedusaHeadAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BossMedusaHeadInv", L"Resources\\Image\\BossMedusaHeadInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(35.0f, 80.0f)))
		, mAnimMove(L"BossMedusaHeaddAnim")
		, mAnimInvMove(L"BossMedusaHeadInvAnim")
		, mAnimMoveSize(48.0f, 56.0f)
		, mAnimOffset(-10.f, -30.f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BossMedusaHead");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
	}

	void BossMedusaHead::Tick()
	{
		GameObject::Tick();
	}
	void BossMedusaHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossMedusaHead::OnCollisionEnter(Collider* other)
	{
	}
	void BossMedusaHead::OnCollisionStay(Collider* other)
	{
	}
	void BossMedusaHead::OnCollisionExit(Collider* other)
	{
	}
}