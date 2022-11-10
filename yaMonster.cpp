#include "yaMonster.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	Monster::Monster()
		: GameObject()
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"MudmanMoveAnim")
		, mAnimMoveSize(28.0f, 29.0f)
		, mAnimOffset(Vector2::ZERO)
		, mAnimCount(2)
		, mAnimDuration(0.15f)
	{
		SetName(L"MudMan");
		mPos = { 800.0f, 500.0f };
		mScale = { 3.0f, 3.0f };
		mpImage = Resources::Load<Image>(L"Monster", L"Resources\\Image\\Mudman.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider());
	}
	Monster::Monster(Vector2 pos)
		: GameObject()
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"MudmanMoveAnim")
		, mAnimMoveSize(28.0f, 29.0f)
		, mAnimOffset(Vector2::ZERO)
		, mAnimCount(2)
		, mAnimDuration(0.15f)
	{
		SetName(L"MudMan");
		mPos = { 800.0f, 500.0f };
		mScale = { 3.0f, 3.0f };
		mpImage = Resources::Load<Image>(L"Monster", L"Resources\\Image\\Mudman.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider());
	}
	Monster::~Monster()
	{
	}
	void Monster::Tick()
	{
		GameObject::Tick();
		Vector2 pos = GetPos();
		SetPos(pos);
	}
	void Monster::Render(HDC hdc)
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

	void Monster::OnCollisionEnter(Collider* other)
	{

	}
	void Monster::OnCollisionStay(Collider* other)
	{

	}
	void Monster::OnCollisionExit(Collider* other)
	{

	}
}