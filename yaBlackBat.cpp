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
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"BlackBatAnim")
		, mAnimMoveSize(49.0f, 37.0f)
		, mAnimOffset(-18.f, -10.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		SetName(L"BlackBat");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"BlackBat", L"Resources\\Image\\BlackBatAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(60.0f, 20.0f)));
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