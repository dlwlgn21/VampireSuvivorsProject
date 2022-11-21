#include "yaBossLionHead.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossLionHead::BossLionHead(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BossLionHead", L"Resources\\Image\\BossLionHeadAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BossLionHeadInv", L"Resources\\Image\\BossLionHeadInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(30.0f, 40.0f)))
		, mAnimMove(L"BossLionHeadAnim")
		, mAnimInvMove(L"BossLionHeadInvAnim")
		, mAnimMoveSize(56.0f, 64.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BossLionHead");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
	}

	void BossLionHead::Tick()
	{
		GameObject::Tick();
	}
	void BossLionHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossLionHead::OnCollisionEnter(Collider* other)
	{
	}
	void BossLionHead::OnCollisionStay(Collider* other)
	{
	}
	void BossLionHead::OnCollisionExit(Collider* other)
	{
	}
}