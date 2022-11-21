#include "yaBossMudMan.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	BossMudMan::BossMudMan(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"BossMudMan", L"Resources\\Image\\BossMudManAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"BossMudManInv", L"Resources\\Image\\BossMudManInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(20.0f, 40.0f)))
		, mAnimMove(L"BossMudManAnim")
		, mAnimInvMove(L"BossMudManInvAnim")
		, mAnimMoveSize(56.0f, 66.0f)
		, mAnimOffset(-15.f, -20.f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		SetName(L"BossMudMan");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
	}

	void BossMudMan::Tick()
	{
		GameObject::Tick();
	}
	void BossMudMan::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BossMudMan::OnCollisionEnter(Collider* other)
	{

	}
	void BossMudMan::OnCollisionStay(Collider* other)
	{

	}
	void BossMudMan::OnCollisionExit(Collider* other)
	{

	}
}