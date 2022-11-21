#include "yaMagision.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	Magision::Magision(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"Magision", L"Resources\\Image\\MagisionAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"MagisionInv", L"Resources\\Image\\MagisionInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(30.0f, 40.0f)))
		, mAnimMove(L"MagisionAnim")
		, mAnimInvMove(L"MagisionAnimInv")
		, mAnimMoveSize(31.0f, 33.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"Magision");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void Magision::Tick()
	{
		GameObject::Tick();
	}
	void Magision::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Magision::OnCollisionEnter(Collider* other)
	{
	}
	void Magision::OnCollisionStay(Collider* other)
	{
	}
	void Magision::OnCollisionExit(Collider* other)
	{
	}
}