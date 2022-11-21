#include "yaBlackBat.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BlackBat::BlackBat(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BlackBat", L"Resources\\Image\\BlackBatAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BlackBatInv", L"Resources\\Image\\BlackBatInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(60.0f, 20.0f)))
		, mAnimMove(L"BlackBatAnim")
		, mAnimInvMove(L"BlackBatInvAnim")
		, mAnimMoveSize(49.0f, 37.0f)
		, mAnimOffset(-18.f, -10.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BlackBat");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void BlackBat::Tick()
	{
		GameObject::Tick();
	}
	void BlackBat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BlackBat::OnCollisionEnter(Collider* other)
	{
	}
	void BlackBat::OnCollisionStay(Collider* other)
	{
	}
	void BlackBat::OnCollisionExit(Collider* other)
	{
	}
}