#include "yaBossBroomWitch.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossBroomWitch::BossBroomWitch(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"BossBroomWitchAnim")
		, mAnimMoveSize(68.0f, 72.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		SetName(L"BossBroomWitch");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"BossBroomWitch", L"Resources\\Image\\BossBroomWitchAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(30.0f, 40.0f)));
	}

	void BossBroomWitch::Tick()
	{
		GameObject::Tick();
	}
	void BossBroomWitch::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossBroomWitch::OnCollisionEnter(Collider* other)
	{
	}
	void BossBroomWitch::OnCollisionStay(Collider* other)
	{
	}
	void BossBroomWitch::OnCollisionExit(Collider* other)
	{
	}
}