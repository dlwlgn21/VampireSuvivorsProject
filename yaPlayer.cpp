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
#include "yaKnife.h"

namespace ya
{
	Player::Player()
		: GameObject({ 1500.0f, 500.0f })
		, mSpeed(300.0f)
		, mPen(CreatePen(PS_DASHDOTDOT, 3, RGB(0, 255, 255)))
		, mBrush(CreateSolidBrush(RGB(153, 204, 255)))
		, mpLeftImage(Resources::Load<Image>(L"PlayerLeft", L"Resources\\Image\\PlayerLeftAnim.bmp"))
		, mpRightImage(Resources::Load<Image>(L"PlayerRight", L"Resources\\Image\\PlayerRightAnim.bmp"))
		, mpLeftHittedImage(Resources::Load<Image>(L"PlayerLeftHitted", L"Resources\\Image\\PlayerLeftHittedAnim.bmp"))
		, mpRightHittedImage(Resources::Load<Image>(L"PlayerRightHitted", L"Resources\\Image\\PlayerRightHittedAnim.bmp"))
		, mAnimSize(34.0f, 34.0f)
		, mAnimOffset(-19.0f, -15.0f)
		, mAnimCount(4)
		, mMinAnimInterval(0.15f)
		, dir(Vector2::ONE)
		, mpAnimator(new PlayerCustomAnimator())
		, mpCollider(new Collider({20.0f, 40.0f}))
		, mHp(100)
		, mePlayerAnimState(ePlayerAnimState::LEFT)
		, KnifeShootInterval(2.0f)
		, KnifeTimer(0.0f)
		, meLookDir(ePlayerLookDirection::RIGHT)
	{
		assert(mpLeftImage != nullptr);
		assert(mpRightImage != nullptr);
		assert(mpLeftHittedImage != nullptr);
		assert(mpRightHittedImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"Player");
		mScale = { 2.0f, 2.0f };
		
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mpLeftImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerAnimState::LEFT);
		mpAnimator->CreateAnimation(mpRightImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerAnimState::RIGHT);
		mpAnimator->CreateAnimation(mpLeftHittedImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerAnimState::LEFT_HITTED);
		mpAnimator->CreateAnimation(mpRightHittedImage, Vector2::ZERO, mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerAnimState::RIGHT_HITTED);
		mpAnimator->Play(mePlayerAnimState);
		
		Camera::SetTarget(this);
	}

	void Player::Tick()
	{
		GameObject::Tick();
		KnifeTimer += Time::DeltaTime();


		if (IS_KEY_DOWN(eKeyCode::D))
		{
			mePlayerAnimState = ePlayerAnimState::RIGHT;
			meLookDir = ePlayerLookDirection::RIGHT;
			mpAnimator->Play(mePlayerAnimState);
		}
		if (IS_KEY_DOWN(eKeyCode::A))
		{
			mePlayerAnimState = ePlayerAnimState::LEFT;
			meLookDir = ePlayerLookDirection::LEFT;
			mpAnimator->Play(mePlayerAnimState);
		}

		if (IS_KEY_PRESSED(eKeyCode::W)) 
		{ 
			if (IS_KEY_PRESSED(eKeyCode::A))
			{
				mPos.x -= mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				mPos.y -= mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				meLookDir = ePlayerLookDirection::UP_LEFT;
				goto PLAY_ANIMATION;
			}
			else if (IS_KEY_PRESSED(eKeyCode::D))
			{
				mPos.x += mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				mPos.y -= mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				meLookDir = ePlayerLookDirection::UP_RIGHT;
				goto PLAY_ANIMATION;
			}
			else
			{ 
				meLookDir = ePlayerLookDirection::UP;
				mPos.y -= mSpeed * Time::DeltaTime(); 
			}
		}
		if (IS_KEY_PRESSED(eKeyCode::S)) 
		{ 
			if (IS_KEY_PRESSED(eKeyCode::A))
			{
				mPos.x -= mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				mPos.y += mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				meLookDir = ePlayerLookDirection::DOWN_LEFT;

				goto PLAY_ANIMATION;
			}
			else if (IS_KEY_PRESSED(eKeyCode::D))
			{
				mPos.x += mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				mPos.y += mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				meLookDir = ePlayerLookDirection::DOWN_RIGHT;
				goto PLAY_ANIMATION;
			}
			else
			{
				meLookDir = ePlayerLookDirection::DOWN;
				mPos.y += mSpeed * Time::DeltaTime(); 
			}
		}
		if (IS_KEY_PRESSED(eKeyCode::A)) 
		{ 
			mPos.x -= mSpeed * Time::DeltaTime(); 
			mePlayerAnimState = ePlayerAnimState::LEFT;
			meLookDir = ePlayerLookDirection::LEFT;
		}
		if (IS_KEY_PRESSED(eKeyCode::D)) 
		{ 
			mPos.x += mSpeed * Time::DeltaTime(); 
			mePlayerAnimState = ePlayerAnimState::RIGHT;
			meLookDir = ePlayerLookDirection::RIGHT;
		}


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

	PLAY_ANIMATION:
		{
			mpAnimator->Play(mePlayerAnimState);
		}
		if (KnifeTimer >= KnifeShootInterval)
		{
			GameObject* pKnife = static_cast<GameObject*>(new Knife(mPos, 10, 1, 400.0f, 1.0f, KnifeShootInterval, static_cast<eKnifeDirection>(meLookDir)));
			Scene* scene = SceneManager::GetCurrentScene();
			scene->AddGameObject(pKnife, eColliderLayer::PLAYER_PROJECTTILE);
			KnifeTimer = 0.0f;
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
		mHp -= 10;
		if (mHp < 0)
		{
			mHp = 100;
		}
	}
	void Player::OnCollisionStay(Collider* other)
	{
		switch (mePlayerAnimState)
		{
		case ePlayerAnimState::LEFT:
			mePlayerAnimState = ePlayerAnimState::LEFT_HITTED;
			break;
		case ePlayerAnimState::RIGHT:
			mePlayerAnimState = ePlayerAnimState::RIGHT_HITTED;
			break;
		default:
			break;
		}
		mpAnimator->Play(mePlayerAnimState);
	}
	void Player::OnCollisionExit(Collider* other)
	{
		switch (mePlayerAnimState)
		{
		case ePlayerAnimState::LEFT_HITTED:
			mePlayerAnimState = ePlayerAnimState::LEFT;
			break;
		case ePlayerAnimState::RIGHT_HITTED:
			mePlayerAnimState = ePlayerAnimState::RIGHT;
			break;
		default:
			break;
		}
		mpAnimator->Play(mePlayerAnimState);
	}

	void Player::WalkComplete()
	{
		/*Missile* pMis = ya::object::Instantiate<Missile>(eColliderLayer::PLAYER_PROJECTTILE);
		pMis->SetPos(mPos);*/
	}


}