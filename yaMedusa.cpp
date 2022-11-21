#include "yaMedusa.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	Medusa::Medusa(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"Medusa", L"Resources\\Image\\MedusaAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"MedusaInv", L"Resources\\Image\\MedusaInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(35.0f, 80.0f)))
		, mAnimMove(L"MedusaAnim")
		, mAnimInvMove(L"MedusaAnimInv")
		, mAnimMoveSize(48.0f, 52.0f)
		, mAnimOffset(-10.f, -30.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"Medusa");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void Medusa::Tick()
	{
		GameObject::Tick();
	}
	void Medusa::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Medusa::OnCollisionEnter(Collider* other)
	{
	}
	void Medusa::OnCollisionStay(Collider* other)
	{
	}
	void Medusa::OnCollisionExit(Collider* other)
	{
	}
}