#include "yaLionHead.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	LionHead::LionHead(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"LionHead", L"Resources\\Image\\LionHeadAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"LionHeadInv", L"Resources\\Image\\LionHeadInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(30.0f, 40.0f)))
		, mAnimMove(L"LionHeadAnim")
		, mAnimInvMove(L"LionHeadAnimInv")
		, mAnimMoveSize(28.0f, 32.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"LionHead");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
	}

	void LionHead::Tick()
	{
		GameObject::Tick();
	}
	void LionHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void LionHead::OnCollisionEnter(Collider* other)
	{
	}
	void LionHead::OnCollisionStay(Collider* other)
	{
	}
	void LionHead::OnCollisionExit(Collider* other)
	{
	}
}