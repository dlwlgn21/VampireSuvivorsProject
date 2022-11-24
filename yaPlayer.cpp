#include <cassert>
#include "Common.h"
#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaPlayerCustomAnimation.h"
#include "yaMissile.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaBackpack.h"
#include "yaObject.h"
#include "yaRigidBody.h"
#include "yaUIManager.h"

namespace ya
{
	Player::Player()
		: GameObject({ 1500.0f, 500.0f })
		, mSpeed(500.0f)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpLeftImage(Resources::Load<Image>(L"PlayerLeft", L"Resources\\Image\\PlayerLeftAnim.bmp"))
		, mpRightImage(Resources::Load<Image>(L"PlayerRight", L"Resources\\Image\\PlayerRightAnim.bmp"))
		, mAnimSize(34.0f, 34.0f)
		, mAnimOffset(-18.0f, -22.0f)
		, mAnimCount(4)
		, mMinAnimInterval(0.15f)
		, mColliderSize(25.0f, 40.0f)
		, dir(Vector2::ONE)
		, mpAnimator(new PlayerCustomAnimator())
		, mpCollider(new Collider(mColliderSize))
		, mHp(100)
		, mEPlayerDir(ePlayerDirection::LEFT)
	{
		assert(mpLeftImage != nullptr);
		assert(mpRightImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"Player");
		mScale = { 2.0f, 2.0f };
		
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mpLeftImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerDirection::LEFT);
		mpAnimator->CreateAnimation(mpRightImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerDirection::RIGHT);
		mpAnimator->Play(mEPlayerDir);
		
		Camera::SetTarget(this);
	}

	void Player::Tick()
	{
		GameObject::Tick();
#if 1
		if (IS_KEY_DOWN(eKeyCode::D))
		{
			mEPlayerDir = ePlayerDirection::RIGHT;
			mpAnimator->Play(mEPlayerDir);
		}
		//if (IS_KEY_DOWN(eKeyCode::W) || IS_KEY_DOWN(eKeyCode::S) || IS_KEY_DOWN(eKeyCode::D))
		//if (IS_KEY_UP(eKeyCode::D))		{ mpAnimator->Play(mAnimMove, false); }
		if (IS_KEY_DOWN(eKeyCode::A))
		{
			mEPlayerDir = ePlayerDirection::LEFT;
			mpAnimator->Play(mEPlayerDir);
		}

		if (IS_KEY_PRESSED(eKeyCode::W)) 
		{ 
			mPos.y -= mSpeed * Time::DeltaTime(); 
			mpAnimator->Play(mEPlayerDir);
		}
		if (IS_KEY_PRESSED(eKeyCode::S)) 
		{ 
			mPos.y += mSpeed * Time::DeltaTime(); 
			mpAnimator->Play(mEPlayerDir);
		}
		if (IS_KEY_PRESSED(eKeyCode::A)) 
		{ 
			mPos.x -= mSpeed * Time::DeltaTime(); 
			mEPlayerDir = ePlayerDirection::LEFT;
			mpAnimator->Play(mEPlayerDir);
		}
		if (IS_KEY_PRESSED(eKeyCode::D)) 
		{ 
			mPos.x += mSpeed * Time::DeltaTime(); 
			mEPlayerDir = ePlayerDirection::RIGHT;
			mpAnimator->Play(mEPlayerDir);
		}
#endif


// RigidBody PART
#if 0
		if (IS_KEY_PRESSED(eKeyCode::W)) { GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY)->AddForce({0.0f, -mSpeed }); }
		if (IS_KEY_PRESSED(eKeyCode::S)) { GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY)->AddForce({ 0.0f, mSpeed }); }
		if (IS_KEY_PRESSED(eKeyCode::A)) { GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY)->AddForce({ -mSpeed, 0.0f }); }
		if (IS_KEY_PRESSED(eKeyCode::D)) { GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY)->AddForce({ mSpeed, 0.0f }); }

#endif

		//if (IS_KEY_UP(eKeyCode::A))		{ mpAnimator->Play(mAnimMoveInv, false); }
		
#if 0
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
			mHp = 100;
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


}