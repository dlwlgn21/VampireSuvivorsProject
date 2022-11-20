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
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"MedusaAnim")
		, mAnimMoveSize(48.0f, 52.0f)
		, mAnimOffset(-10.f, -30.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		SetName(L"Medusa");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"Medusa", L"Resources\\Image\\MedusaAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(35.0f, 80.0f)));
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