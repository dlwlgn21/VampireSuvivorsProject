#include "yaBroomWitch.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BroomWitch::BroomWitch(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BroomWitch", L"Resources\\Image\\BroomWitchAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BroomWitchInv", L"Resources\\Image\\BroomWitchInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(30.0f, 40.0f)))
		, mAnimMove(L"BroomWitchAnim")
		, mAnimInvMove(L"BroomWitchAnimInv")
		, mAnimMoveSize(34.0f, 36.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BroomWitch");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void BroomWitch::Tick()
	{
		GameObject::Tick();
	}
	void BroomWitch::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BroomWitch::OnCollisionEnter(Collider* other)
	{
	}
	void BroomWitch::OnCollisionStay(Collider* other)
	{
	}
	void BroomWitch::OnCollisionExit(Collider* other)
	{
	}
}