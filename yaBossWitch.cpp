#include "yaBossWitch.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossWitch::BossWitch(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"BossWitchAnim")
		, mAnimMoveSize(53.0f, 50.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		SetName(L"BossWitch");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"BossWitch", L"Resources\\Image\\BossWitchAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(30.0f, 40.0f)));
	}

	void BossWitch::Tick()
	{
		GameObject::Tick();
	}
	void BossWitch::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossWitch::OnCollisionEnter(Collider* other)
	{
	}
	void BossWitch::OnCollisionStay(Collider* other)
	{
	}
	void BossWitch::OnCollisionExit(Collider* other)
	{
	}
}