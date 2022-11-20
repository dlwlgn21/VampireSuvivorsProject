#include "yaMedusaHead.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	MedusaHead::MedusaHead(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"GreenMedusaHeadAnim")
		, mAnimMoveSize(24.0f, 28.0f)
		, mAnimOffset(-10.f, -15.f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
	{
		SetName(L"GreenMedusaHead");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"GreenMedusaHead", L"Resources\\Image\\GreenMedusaHeadAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(20.0f, 20.0f)));
	}

	void MedusaHead::Tick()
	{
		GameObject::Tick();
	}
	void MedusaHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MedusaHead::OnCollisionEnter(Collider* other)
	{
	}
	void MedusaHead::OnCollisionStay(Collider* other)
	{
	}
	void MedusaHead::OnCollisionExit(Collider* other)
	{
	}
}