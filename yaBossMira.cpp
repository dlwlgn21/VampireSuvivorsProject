#include "yaBossMira.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossMira::BossMira(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"BossMiraAnim")
		, mAnimMoveSize(35.0f, 48.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		SetName(L"BossMira");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"BossMira", L"Resources\\Image\\BossMiraAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(30.0f, 60.0f)));
	}

	void BossMira::Tick()
	{
		GameObject::Tick();
	}
	void BossMira::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossMira::OnCollisionEnter(Collider* other)
	{
	}
	void BossMira::OnCollisionStay(Collider* other)
	{
	}
	void BossMira::OnCollisionExit(Collider* other)
	{
	}
}