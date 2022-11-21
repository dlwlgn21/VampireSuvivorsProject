#include "yaMiniHeadDurahan.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	MiniHeadDurahan::MiniHeadDurahan(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"MiniHeadDurahan", L"Resources\\Image\\MIniHeadDurahanAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"MiniHeadDurahanInv", L"Resources\\Image\\MIniHeadDurahanInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(30.0f, 40.0f)))
		, mAnimMove(L"MiniHeadDurahanAnim")
		, mAnimInvMove(L"MiniHeadDurahanAnimInv")
		, mAnimMoveSize(32.0f, 29.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"MiniHeadDurahan");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void MiniHeadDurahan::Tick()
	{
		GameObject::Tick();
	}
	void MiniHeadDurahan::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MiniHeadDurahan::OnCollisionEnter(Collider* other)
	{
	}
	void MiniHeadDurahan::OnCollisionStay(Collider* other)
	{
	}
	void MiniHeadDurahan::OnCollisionExit(Collider* other)
	{
	}
}