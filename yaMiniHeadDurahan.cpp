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
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"MiniHeadDurahanAnim")
		, mAnimMoveSize(32.0f, 29.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		SetName(L"MiniHeadDurahan");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"MiniHeadDurahan", L"Resources\\Image\\MIniHeadDurahanAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(30.0f, 40.0f)));
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