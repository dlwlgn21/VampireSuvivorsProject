#include "yaBossWhiteBat.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossWhiteBat::BossWhiteBat(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BossWhiteBat", L"Resources\\Image\\BossWhiteBatAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"InvBossWhiteBat", L"Resources\\Image\\InvBossWhithBatAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(30.0f, 20.0f)))
		, mAnimMove(L"BossWhiteBatAnim")
		, mAnimInvMove(L"InvBossWhiteBatAnim")
		, mAnimMoveSize(25.0f, 23.0f)
		, mAnimOffset(-9.f, -10.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BossWhiteBat");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);

	}

	void BossWhiteBat::Tick()
	{
		GameObject::Tick();
	}
	void BossWhiteBat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossWhiteBat::OnCollisionEnter(Collider* other)
	{
	}
	void BossWhiteBat::OnCollisionStay(Collider* other)
	{
	}
	void BossWhiteBat::OnCollisionExit(Collider* other)
	{
	}
}