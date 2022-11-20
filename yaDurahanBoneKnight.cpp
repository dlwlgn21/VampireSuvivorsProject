#include "yaDurahanBoneKnight.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	DurahanBoneKnight::DurahanBoneKnight(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"DurahanBoneKnightAnim")
		, mAnimMoveSize(34.0f, 36.0f)
		, mAnimOffset(-18.f, -25.f)
		, mAnimCount(2)
		, mAnimDuration(0.15f)
	{
		SetName(L"DurahanBoneKnight");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"DurahanBoneKnight", L"Resources\\Image\\DurahanBoneKnightAnim.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(30.0f, 40.0f)));
	}

	void DurahanBoneKnight::Tick()
	{
		GameObject::Tick();
	}
	void DurahanBoneKnight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DurahanBoneKnight::OnCollisionEnter(Collider* other)
	{
	}
	void DurahanBoneKnight::OnCollisionStay(Collider* other)
	{
	}
	void DurahanBoneKnight::OnCollisionExit(Collider* other)
	{
	}
}