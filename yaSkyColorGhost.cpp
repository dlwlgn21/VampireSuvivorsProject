#include "yaSkyColorGhost.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	SkyColorGhost::SkyColorGhost(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"SkyColorGhost", L"Resources\\Image\\SkyColorGhostAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"SkyColorGhostInv", L"Resources\\Image\\SkyColorGhostInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(20.0f, 40.0f)))
		, mAnimMove(L"SkyColorGhostAnim")
		, mAnimInvMove(L"SkyColorGhostInvAnim")
		, mAnimMoveSize(27.0f, 30.0f)
		, mAnimOffset(-10.f, -15.f)
		, mAnimCount(3)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"SkyColorGhost");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}


	void SkyColorGhost::Tick()
	{
		GameObject::Tick();
	}
	void SkyColorGhost::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SkyColorGhost::OnCollisionEnter(Collider* other)
	{
	}
	void SkyColorGhost::OnCollisionStay(Collider* other)
	{
	}
	void SkyColorGhost::OnCollisionExit(Collider* other)
	{
	}


}