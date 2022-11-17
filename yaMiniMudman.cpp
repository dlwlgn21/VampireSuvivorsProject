#include "yaMiniMudman.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	//Monster::Monster()
	//	: GameObject()
	//	, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
	//	, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
	//	, mpImage(nullptr)
	//	, mpAnimator(nullptr)
	//	, mAnimMove(L"MudmanMoveAnim")
	//	, mAnimMoveSize(28.0f, 29.0f)
	//	, mAnimOffset(Vector2::ZERO)
	//	, mAnimCount(1)
	//	, mAnimDuration(0.15f)
	//{
	//	SetName(L"MudMan");
	//	mPos = { 800.0f, 500.0f };
	//	mScale = { 3.0f, 3.0f };
	//	mpImage = Resources::Load<Image>(L"Monster", L"Resources\\Image\\Mudman.bmp");
	//	assert(mpImage != nullptr);
	//	mpAnimator = new Animator();
	//	AddComponent(mpAnimator);
	//	mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
	//	mpAnimator->Play(mAnimMove, true);
	//	AddComponent(new Collider());
	//}
	MiniMudman::MiniMudman(Vector2 pos)
		: GameObject(pos)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mAnimMove(L"MudmanMoveAnim")
		, mAnimMoveSize(28.0f, 31.0f)
		, mAnimOffset(-15.f, -20.f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
	{
		SetName(L"MudMan");
		mScale = { 2.0f, 2.0f };
		mpImage = Resources::Load<Image>(L"MiniMudman", L"Resources\\Image\\Mudman5m.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(mAnimMove, mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->Play(mAnimMove, true);
		AddComponent(new Collider(Vector2(20.0f, 40.0f)));
	}
	MiniMudman::~MiniMudman()
	{
	}
	void MiniMudman::Tick()
	{
		GameObject::Tick();
	}
	void MiniMudman::Render(HDC hdc)
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

	void MiniMudman::OnCollisionEnter(Collider* other)
	{

	}
	void MiniMudman::OnCollisionStay(Collider* other)
	{

	}
	void MiniMudman::OnCollisionExit(Collider* other)
	{

	}
}