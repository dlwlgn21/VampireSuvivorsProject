#include "yaBossMira.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossMira::BossMira(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BossMira", L"Resources\\Image\\BossMiraAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BossMiraInv", L"Resources\\Image\\BossMiraInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(30.0f, 60.0f)))
		, mAnimMove(L"BossMiraAnim")
		, mAnimInvMove(L"BossMiraInvAnim")
		, mAnimMoveSize(35.0f, 48.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BossMira");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
	}

	void BossMira::Tick()
	{
		GameObject::Tick();
	}
	void BossMira::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossMira::OnCollisionEnter(Collider* other)
	{
	}
	void BossMira::OnCollisionStay(Collider* other)
	{
	}
	void BossMira::OnCollisionExit(Collider* other)
	{
	}
}