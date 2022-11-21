#include "yaBoomGhost.h"
#include "yaImage.h";
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	BoomGhost::BoomGhost(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BoomGhost", L"Resources\\Image\\BoomGhostAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BoomGhostInv", L"Resources\\Image\\BoomGhostInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(20.0f, 40.0f)))
		, mAnimMove(L"BoomGhostMoveAnim")
		, mAnimInvMove(L"BoomGhostMoveInvAnim")
		, mAnimMoveSize(33.0f, 34.0f)
		, mAnimOffset(-15.f, -20.f)
		, mAnimCount(4)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"BoomGhost");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void BoomGhost::Tick()
	{
		GameObject::Tick();
		Vector2 pos = GetPos();
		SetPos(pos);
	}
	void BoomGhost::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BoomGhost::OnCollisionEnter(Collider* other)
	{

	}
	void BoomGhost::OnCollisionStay(Collider* other)
	{

	}
	void BoomGhost::OnCollisionExit(Collider* other)
	{

	}
}