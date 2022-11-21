#include "yaGrayMira.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"


namespace ya
{
	GrayMira::GrayMira(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"GreenMira", L"Resources\\Image\\GrayMiraAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"GreenMiraInv", L"Resources\\Image\\GrayMiraInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(20.0f, 40.0f)))
		, mAnimMove(L"GrayMiraAnim")
		, mAnimInvMove(L"GrayMiraAnimInv")
		, mAnimMoveSize(34.0f, 31.0f)
		, mAnimOffset(-10.f, -15.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"GrayMira");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void GrayMira::Tick()
	{
		GameObject::Tick();
	}
	void GrayMira::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void GrayMira::OnCollisionEnter(Collider* other)
	{
	}
	void GrayMira::OnCollisionStay(Collider* other)
	{
	}
	void GrayMira::OnCollisionExit(Collider* other)
	{
	}
}