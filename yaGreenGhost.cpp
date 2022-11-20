#include "yaGreenGhost.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	GreenGhost::GreenGhost(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"GreenGhostAnim")
		, mAnimMoveSize(18.0f, 31.0f)
		, mAnimOffset(-10.f, -15.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		SetName(L"GreenGhost");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"GreenGhost", L"Resources\\Image\\GreenGhostAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(20.0f, 30.0f)));
	}

	void GreenGhost::Tick()
	{
		GameObject::Tick();
	}
	void GreenGhost::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void GreenGhost::OnCollisionEnter(Collider* other)
	{
	}
	void GreenGhost::OnCollisionStay(Collider* other)
	{
	}
	void GreenGhost::OnCollisionExit(Collider* other)
	{
	}
}