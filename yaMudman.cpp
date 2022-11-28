#include "yaMudman.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	Mudman::Mudman(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(Resources::Load<Image>(L"Mudman", L"Resources\\Image\\MudmanAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"MudmanInv", L"Resources\\Image\\MudmanInvAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(20.0f, 40.0f)))
		, mAnimMove(L"MudmanAnim")
		, mAnimInvMove(L"MudmanAnimInv")
		, mAnimMoveSize(28.0f, 31.0f)
		, mAnimOffset(-15.f, -20.f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
		, mHP(15)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"Mudman");
		mScale = { 2.0f, 2.0f };
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void Mudman::Tick()
	{
		GameObject::Tick();
	}
	void Mudman::Render(HDC hdc)
	{
	/*	Vector2 fPos;
		fPos.x = mPos.x - mpImage->GetWidth() * (mScale.x / 2);
		fPos.y = mPos.y - mpImage->GetWidth() * (mScale.x / 2);
		fPos = Camera::ToCameraPos(fPos);
		TransparentBlt(
			hdc,
			static_cast<int>(fPos.x),
			static_cast<int>(fPos.y),
			static_cast<int>(mpImage->GetWidth() * mScale.x),
			static_cast<int>(mpImage->GetHeight() * mScale.y),

			mpImage->GetDC(),
			0, 0,
			mpImage->GetWidth(),
			mpImage->GetHeight(),
			RGB(255, 0, 255)
		);*/

		GameObject::Render(hdc);
	}

	void Mudman::OnCollisionEnter(Collider* other)
	{

	}
	void Mudman::OnCollisionStay(Collider* other)
	{

	}
	void Mudman::OnCollisionExit(Collider* other)
	{

	}
}