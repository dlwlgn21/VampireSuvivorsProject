#include "yaBossNesparados.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossNesparados::BossNesparados(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"BossDesparadosAnim")
		, mAnimMoveSize(40.0f, 48.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		SetName(L"BossNesparados");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"BossNesparados", L"Resources\\Image\\BossNesparadosAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(30.0f, 60.0f)));
	}

	void BossNesparados::Tick()
	{
		GameObject::Tick();
	}
	void BossNesparados::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossNesparados::OnCollisionEnter(Collider* other)
	{
	}
	void BossNesparados::OnCollisionStay(Collider* other)
	{
	}
	void BossNesparados::OnCollisionExit(Collider* other)
	{
	}
}