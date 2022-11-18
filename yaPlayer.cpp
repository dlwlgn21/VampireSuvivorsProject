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
#include "yaRigidBody.h"
#include "yaUIManager.h"

namespace ya
{
	Player::Player()
		: GameObject()
		, mSpeed(500.0f)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpIdleImage(nullptr)
		, mpMoveImage(nullptr)
		, mpMoveInvImage(nullptr)
		, mAnimMove(L"Move")
		, mAnimMoveInv(L"MoveInverse")
		, mAnimMoveSize(34.0f, 34.0f)
		, mAnimOffset(-18.0f, -22.0f)
		, mAnimCount(4)
		, mAnimRowInterval(130.0f)
		, mAnimDuration(0.15f)
		, mColliderScale(25.0f, 40.0f)
		, dir(Vector2::ONE)
		, mHp(100)
	{
		SetName(L"Player");
		mPos = { 1500.0f, 500.0f };
		mScale = { 2.0f, 2.0f };
		mpMoveImage = Resources::Load<Image>(L"PlayerMoveAnim", L"Resources\\Image\\CharacterMove.bmp");
		assert(mpMoveImage != nullptr);
		mpMoveInvImage = Resources::Load<Image>(L"PlayerMoveInverseAnim", L"Resources\\Image\\CharacterMoveInverse.bmp");
		assert(mpMoveInvImage != nullptr);
		
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		createAnimation(mAnimMove,		mpMoveImage,	Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		createAnimation(mAnimMoveInv,	mpMoveInvImage,	Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);

		// mpAnimator->GetCompleteEvent(mAnimIdle) = std::bind(&Player::WalkComplete, this);
		// 이거 내가 따로 다시 공부해야함. 마지막 이벤트에 고고
		// mpAnimator->mCompleteEvent = std::bind(&Player::WalkComplete, this);
		AddComponent(new Collider(mColliderScale)); 
		//AddComponent(new RigidBody());
		Camera::SetTarget(this);
	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		GameObject::Tick();
#if 1
		if (IS_KEY_PRESSED(eKeyCode::W)) { mPos.y -= mSpeed * Time::DeltaTime(); }
		if (IS_KEY_PRESSED(eKeyCode::S)) { mPos.y += mSpeed * Time::DeltaTime(); }
		if (IS_KEY_PRESSED(eKeyCode::A)) { mPos.x -= mSpeed * Time::DeltaTime(); }
		if (IS_KEY_PRESSED(eKeyCode::D)) { mPos.x += mSpeed * Time::DeltaTime(); }
#endif


// RigidBody PART
#if 0
		if (IS_KEY_PRESSED(eKeyCode::W)) { GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY)->AddForce({0.0f, -mSpeed }); }
		if (IS_KEY_PRESSED(eKeyCode::S)) { GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY)->AddForce({ 0.0f, mSpeed }); }
		if (IS_KEY_PRESSED(eKeyCode::A)) { GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY)->AddForce({ -mSpeed, 0.0f }); }
		if (IS_KEY_PRESSED(eKeyCode::D)) { GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY)->AddForce({ mSpeed, 0.0f }); }

#endif
		if (IS_KEY_DOWN(eKeyCode::D)) { mpAnimator->Play(mAnimMove, true); }
		//if (IS_KEY_DOWN(eKeyCode::W) || IS_KEY_DOWN(eKeyCode::S) || IS_KEY_DOWN(eKeyCode::D))
		if (IS_KEY_UP(eKeyCode::D))		{ mpAnimator->Play(mAnimMove, false); }
		if (IS_KEY_DOWN(eKeyCode::A))	{ mpAnimator->Play(mAnimMoveInv, true); }
		if (IS_KEY_UP(eKeyCode::A))		{ mpAnimator->Play(mAnimMoveInv, false); }
		
#if 1
		if (IS_KEY_DOWN(eKeyCode::SPACE))
		{
// RigidBodyPart
#if 0

			RigidBody* pRB = GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY);
			Vector2 velocity = pRB->GetVelocity();
			velocity.y -= 500.0f;
			pRB->SetVelocity(velocity);
			pRB->SetIsGround(false);
#endif
			// FOR TEST
			// UIManager::Pop(eUIType::OPTIOIN);
		}
#endif


#if 0
		if (IS_KEY_DOWN(eKeyCode::L_BUTTON))
		{
// FOR AsortLock class
			Missile* pMis = ya::object::Instantiate<Missile>(eColliderLayer::PLAYER_PROJECTTILE);
			//pMis->mDestPos = Input::GetMousePos();
			//pMis->mDir = pMis->mDestPos - pMis->GetPos();
			pMis->SetPos(mPos);
			pMis->mDestPos = Input::GetMousePos() - mPos;
			dir = yamath::Rotate(dir, 5.0f);
			pMis->mDir = dir;
		}
#endif
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
		mHp -= 10;
		if (mHp < 0)
		{
			mHp = 0;
		}
	}
	void Player::OnCollisionStay(Collider* other)
	{
	}
	void Player::OnCollisionExit(Collider* other)
	{
	}

	void Player::WalkComplete()
	{
		/*Missile* pMis = ya::object::Instantiate<Missile>(eColliderLayer::PLAYER_PROJECTTILE);
		pMis->SetPos(mPos);*/
	}

	void Player::createAnimation(const std::wstring& name, Image* image, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		mpAnimator->CreateAnimation(
			name,
			image,
			leftTop,
			size,
			offset,
			spriteLength,
			duration
		);
	}

}