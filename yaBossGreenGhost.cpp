#include "yaBossGreenGhost.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossGreenGhost::BossGreenGhost(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BossGreenGhost", L"Resources\\Image\\BossGreenGhostAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BossGreenGhostInv", L"Resources\\Image\\BossGreenGhostInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(20.0f, 30.0f)))
		, mAnimMove(L"BossGreenGhostAnim")
		, mAnimInvMove(L"BossGreenGhostInvAnim")
		, mAnimMoveSize(36.0f, 62.0f)
		, mAnimOffset(-10.f, -15.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BossGreenGhost");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void BossGreenGhost::Tick()
	{
		GameObject::Tick();
	}
	void BossGreenGhost::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossGreenGhost::OnCollisionEnter(Collider* other)
	{
	}
	void BossGreenGhost::OnCollisionStay(Collider* other)
	{
	}
	void BossGreenGhost::OnCollisionExit(Collider* other)
	{
	}
}