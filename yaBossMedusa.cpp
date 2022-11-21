#include "yaBossMedusa.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossMedusa::BossMedusa(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BossMedusa", L"Resources\\Image\\BossMedusaAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BossMedusaInv", L"Resources\\Image\\BossMedusaInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(35.0f, 80.0f)))
		, mAnimMove(L"BossMedusaAnim")
		, mAnimInvMove(L"BossMedusaInvAnim")
		, mAnimMoveSize(96.0f, 104.0f)
		, mAnimOffset(-10.f, -30.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BossMedusa");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
	}

	void BossMedusa::Tick()
	{
		GameObject::Tick();
	}
	void BossMedusa::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossMedusa::OnCollisionEnter(Collider* other)
	{
	}
	void BossMedusa::OnCollisionStay(Collider* other)
	{
	}
	void BossMedusa::OnCollisionExit(Collider* other)
	{
	}
}