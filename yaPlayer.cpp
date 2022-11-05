#include <cassert>
#include "Common.h"
#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaMissile.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaBackpack.h"
#include "yaObject.h"

namespace ya
{
	Player::Player()
		: GameObject()
		, mSpeed(500.0f)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpImage(nullptr)
		, mAnimIdle(L"Idle")
		, mAnimMoveUp(L"MoveUp")
		, mAnimMoveDown(L"MoveDown")
		, mAnimMoveLeft(L"MoveLeft")
		, mAnimMoveRight(L"MoveRight")
		, mAnimSize(120.0f, 130.0f)
		, mAnimRowInterval(130.0f)
		, animDuration(0.1f)
	{
		SetName(L"Player");
		mPos = { 500.0f, 500.0f };
		mScale = { 3.0f, 3.0f };
		mpImage = Resources::Load<Image>(L"Player", L"Resources\\Image\\link.bmp");
		assert(mpImage != nullptr);

		mpAnimator = new Animator();

		createAnimation(mAnimIdle, Vector2(0.0f, 0.0f), mAnimSize, Vector2(0.0f, 0.0f), 3, animDuration);
		createAnimation(mAnimMoveDown, Vector2(0.0f, 520.0f), mAnimSize, Vector2(0.0f, 0.0f), 10, animDuration);
		createAnimation(mAnimMoveLeft, Vector2(0.0f, 650.0f), mAnimSize, Vector2(0.0f, 0.0f), 10, animDuration);
		createAnimation(mAnimMoveUp, Vector2(0.0f, 780.0f), mAnimSize, Vector2(0.0f, 0.0f), 10, animDuration);
		createAnimation(mAnimMoveRight, Vector2(0.0f, 910.0f), mAnimSize, Vector2(0.0f, 0.0f), 10, animDuration);

		mpAnimator->Play(mAnimIdle, true);

		// 이거 내가 따로 다시 공부해야함. 마지막 이벤트에 고고
		mpAnimator->mCompleteEvent = std::bind(&Player::WalkComplete, this);

		AddComponent(new Collider());
		AddComponent(mpAnimator);
		Camera::SetTarget(this);
	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		GameObject::Tick();
		if (IS_KEY_PRESSED(eKeyCode::W)) { mPos.y -= mSpeed * Time::DeltaTime(); }
		if (IS_KEY_PRESSED(eKeyCode::S)) { mPos.y += mSpeed * Time::DeltaTime(); }
		if (IS_KEY_PRESSED(eKeyCode::A)) { mPos.x -= mSpeed * Time::DeltaTime(); }
		if (IS_KEY_PRESSED(eKeyCode::D)) { mPos.x += mSpeed * Time::DeltaTime(); }

		if (IS_KEY_DOWN(eKeyCode::W)) { mpAnimator->Play(mAnimMoveUp, true); }
		if (IS_KEY_DOWN(eKeyCode::S)) { mpAnimator->Play(mAnimMoveDown, true); }
		if (IS_KEY_DOWN(eKeyCode::A)) { mpAnimator->Play(mAnimMoveLeft, true); }
		if (IS_KEY_DOWN(eKeyCode::D)) { mpAnimator->Play(mAnimMoveRight, true); }

		if (IS_KEY_UP(eKeyCode::W)) { mpAnimator->Play(mAnimIdle, true); }
		if (IS_KEY_UP(eKeyCode::S)) { mpAnimator->Play(mAnimIdle, true); }
		if (IS_KEY_UP(eKeyCode::A)) { mpAnimator->Play(mAnimIdle, true); }
		if (IS_KEY_UP(eKeyCode::D)) { mpAnimator->Play(mAnimIdle, true); }

		if (IS_KEY_DOWN(eKeyCode::SPACE))
		{
			Missile* missile = ya::object::Instantiate<Missile>(eColliderLayer::PLAYER_PROJECTTILE);
			missile->SetPos((GetPos() + (mScale / 2.0f)) - (missile->GetScale() / 2.0f));
		}
		if (IS_KEY_DOWN(eKeyCode::I))
		{
			Scene* currScene = SceneManager::GetCurrentScene();
			currScene->AddGameObject(new Backpack(), eColliderLayer::BACKPACK);
		}

	}

	void Player::Render(HDC hdc)
	{
		//Pen	pen(hdc, mPen);
		//Brush brush(hdc, mBrush);

		//Rectangle(hdc,
		//	static_cast<int>(mPos.x),
		//	static_cast<int>(mPos.y),
		//	static_cast<int>(mPos.x + mScale.x),
		//	static_cast<int>(mPos.y + mScale.y)
		//);
		//BitBlt(
		//	hdc,
		//	static_cast<int>(mPos.x),
		//	static_cast<int>(mPos.y),
		//	mImage->GetWidth(),
		//	mImage->GetHeight(),
		//	
		//	mImage->GetDC(),
		//	0,
		//	0,
		//	SRCCOPY
		//);

	/*	Vector2 fPos;
		fPos.x = mPos.x - mImage->GetWidth() * (mScale.x / 2);
		fPos.y = mPos.y - mImage->GetWidth() * (mScale.x / 2);
		fPos = Camera::ToCameraPos(fPos);
		TransparentBlt(
			hdc,
			static_cast<int>(fPos.x),
			static_cast<int>(fPos.y),
			static_cast<int>(mImage->GetWidth() * mScale.x),
			static_cast<int>(mImage->GetHeight() * mScale.y),

			mImage->GetDC(),
			0, 0,
			mImage->GetWidth(),
			mImage->GetHeight(),
			RGB(255, 0, 255)
		);*/

		GameObject::Render(hdc);
	}


	void Player::OnCollisionEnter(Collider* other)
	{

	}
	void Player::OnCollisionStay(Collider* other)
	{

	}
	void Player::OnCollisionExit(Collider* other)
	{

	}

	void Player::WalkComplete()
	{

	}

	void Player::createAnimation(const std::wstring& name, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		mpAnimator->CreateAnimation(
			name,
			mpImage,
			leftTop,
			size,
			offset,
			spriteLength,
			duration
		);
	}

}