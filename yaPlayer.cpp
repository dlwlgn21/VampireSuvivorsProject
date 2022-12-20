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
#include "yaKnifeObjectPool.h"
#include "yaWeaponObjectPool.h"
#include "yaRuneTracer.h"
#include "yaMonster.h"
#include "yaPlayerLevelUpManager.h"
#include "yaAxe.h"
#include "yaFireWand.h"

namespace ya
{
	Player::Player()
		: GameObject({ 1500.0f, 500.0f })
		, mMoveSpeed(300.0f)
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
		, mpCollider(new Collider({ 20.0f, 40.0f }))
		, mLevel(1)
		, mExp(0)
		, mHp(100)
		, mKnockbackValue(0.5f)
		, mAmour(0)
		, mWeaponSpeed(700.0f)
		, mWeaponDamageCoefficient(1.0f)
		, mWeaponSpeedCoefficient(1.0f)
		, mePlayerAnimState(ePlayerAnimState::LEFT)
		, mKnifeShootTimer(0.0f)
		, meLookDir(ePlayerLookDirection::RIGHT)
		, mpKnifeObjPool(new KnifeObjectPool(MAX_KNIFE_COUNT))
		, mpRuneObjPool(nullptr)
		, mRuneShootTimer(0.0f)
		, mpAxeObjPool(nullptr)
		, mAxeShootTimer(0.0f)
		, mpFireWandObjPool(nullptr)
		, mFireWandShootTimer(0.0f)
		, mPlyerItemLevelStat(PlayerItemLevelStat())
		, mKnifeStat(WeaponStat(WEAPON_KNIFE_INITIAL_DAMAGE, 1, 0, 700.0f, TEST_WEAPON_SHOOT_INTERVAL))
		, mFireWandStat(WeaponStat(WEAPON_FIRE_WAND_INITIAL_DAMAGE, 5, 0, 500.0f, TEST_WEAPON_SHOOT_INTERVAL))
		, mRuneStat(WeaponStat(WEAPON_RUNE_INITIAL_DAMAGE, 1, 0, 600.0f, TEST_WEAPON_SHOOT_INTERVAL))
		, mAxeStat(WeaponStat(WEAPON_AXE_INITIAL_DAMAGE, 1, 0, 700.0f, TEST_WEAPON_SHOOT_INTERVAL))
		, mbIsWeaponFireWandOpen(false)
		, mbIsWeaponRuneOpen(false)
		, mbIsWeaponAxeOpen(false)
	{
		assert(mpLeftImage != nullptr);
		assert(mpRightImage != nullptr);
		assert(mpLeftHittedImage != nullptr);
		assert(mpRightHittedImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		assert(mpKnifeObjPool != nullptr);
		//assert(mpRuneTracerPool != nullptr);

		SetName(L"Player");
		mScale = { 2.0f, 2.0f };

		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpAnimator->CreateAnimation(mpLeftImage, mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerAnimState::LEFT);
		mpAnimator->CreateAnimation(mpRightImage, mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerAnimState::RIGHT);
		mpAnimator->CreateAnimation(mpLeftHittedImage, mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerAnimState::LEFT_HITTED);
		mpAnimator->CreateAnimation(mpRightHittedImage,  mAnimSize, mAnimOffset, mAnimCount, mMinAnimInterval, ePlayerAnimState::RIGHT_HITTED);
		mpAnimator->Play(mePlayerAnimState);
		LevelUpUIManager::GetInstance().SetPlayer(this);
		Camera::SetTarget(this);
	}

	Player::~Player()
	{
		if (mpKnifeObjPool != nullptr)
		{
			delete mpKnifeObjPool;
		}
		if (mpRuneObjPool != nullptr)
		{
			delete mpRuneObjPool;
		}
		if (mpAxeObjPool != nullptr)
		{
			delete mpAxeObjPool;
		}
		if (mpFireWandObjPool != nullptr)
		{
			delete mpFireWandObjPool;
		}
	}

	void Player::Tick()
	{
		GameObject::Tick();

		mKnifeShootTimer += Time::DeltaTime();
		if (mbIsWeaponRuneOpen)
			{ mRuneShootTimer += Time::DeltaTime(); }
		if (mbIsWeaponAxeOpen)
			{ mAxeShootTimer += Time::DeltaTime(); }
		if (mbIsWeaponFireWandOpen)
			{ mFireWandShootTimer += Time::DeltaTime(); }

		if (IS_KEY_DOWN(eKeyCode::D))
		{
			mePlayerAnimState = ePlayerAnimState::RIGHT;
			mpAnimator->Play(mePlayerAnimState);
		}
		if (IS_KEY_DOWN(eKeyCode::A))
		{
			mePlayerAnimState = ePlayerAnimState::LEFT;
			mpAnimator->Play(mePlayerAnimState);
		}

		if (IS_KEY_PRESSED(eKeyCode::W))
		{
			if (IS_KEY_PRESSED(eKeyCode::A))
			{
				mPos.x -= mMoveSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				mPos.y -= mMoveSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				meLookDir = ePlayerLookDirection::UP_LEFT;
				goto PLAY_ANIMATION;
			}
			else if (IS_KEY_PRESSED(eKeyCode::D))
			{
				mPos.x += mMoveSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				mPos.y -= mMoveSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				meLookDir = ePlayerLookDirection::UP_RIGHT;
				goto PLAY_ANIMATION;
			}
			else
			{
				meLookDir = ePlayerLookDirection::UP;
				mPos.y -= mMoveSpeed * Time::DeltaTime();
				goto PLAY_ANIMATION;
			}
		}
		if (IS_KEY_PRESSED(eKeyCode::S))
		{
			if (IS_KEY_PRESSED(eKeyCode::A))
			{
				mPos.x -= mMoveSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				mPos.y += mMoveSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				meLookDir = ePlayerLookDirection::DOWN_LEFT;

				goto PLAY_ANIMATION;
			}
			else if (IS_KEY_PRESSED(eKeyCode::D))
			{
				mPos.x += mMoveSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				mPos.y += mMoveSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
				meLookDir = ePlayerLookDirection::DOWN_RIGHT;
				goto PLAY_ANIMATION;
			}
			else
			{
				meLookDir = ePlayerLookDirection::DOWN;
				mPos.y += mMoveSpeed * Time::DeltaTime();
				goto PLAY_ANIMATION;
			}
		}
		if (IS_KEY_PRESSED(eKeyCode::A))
		{
			mPos.x -= mMoveSpeed * Time::DeltaTime();
			mePlayerAnimState = ePlayerAnimState::LEFT;
			meLookDir = ePlayerLookDirection::LEFT;
		}
		if (IS_KEY_PRESSED(eKeyCode::D))
		{
			mPos.x += mMoveSpeed * Time::DeltaTime();
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
		if (mKnifeShootTimer >= mKnifeStat.ShootInterval)
		{
			//mKnifeObjPool.Get(mPos, 10, 1, 1000.0f, 1.0f, KnifeShootInterval, static_cast<eKnifeDirection>(meLookDir));

			for (int i = 0; i < mKnifeStat.Count; ++i)
			{
				GameObject* pKnife = static_cast<GameObject*>(mpKnifeObjPool->Get(mPos, mKnifeStat.Damage, mKnifeStat.Speed * mWeaponSpeedCoefficient, mKnockbackValue, mKnifeStat.ShootInterval, static_cast<eKnifeDirection>(meLookDir), mpKnifeObjPool));
				Scene* scene = SceneManager::GetCurrentScene();
				scene->AddWeaponObject(pKnife);
			}
			mKnifeShootTimer = 0.0f;
		}

		if (mbIsWeaponRuneOpen)
		{
			if (mRuneShootTimer >= mRuneStat.ShootInterval)
			{
				for (int i = 0; i < mRuneStat.Count; ++i)
				{
					GameObject* pRune = static_cast<GameObject*>(mpRuneObjPool->Get(mPos, mRuneStat.Damage, mRuneStat.Speed * mWeaponSpeedCoefficient, mKnockbackValue, mRuneStat.ShootInterval, mpRuneObjPool));
					Scene* scene = SceneManager::GetCurrentScene();
					scene->AddWeaponObject(pRune);
				}
				mRuneShootTimer = 0.0f;
			}
		}

		if (mbIsWeaponAxeOpen)
		{
			if (mAxeShootTimer >= mAxeStat.ShootInterval)
			{
				for (int i = 0; i < mAxeStat.Count; ++i)
				{
					GameObject* pAxe = static_cast<GameObject*>(mpAxeObjPool->Get(mPos, mAxeStat.Damage, mAxeStat.Speed * mWeaponSpeedCoefficient, mKnockbackValue, mAxeStat.ShootInterval, mpAxeObjPool));
					Scene* scene = SceneManager::GetCurrentScene();
					scene->AddWeaponObject(pAxe);
				}
				mAxeShootTimer = 0.0f;
			}
		}

		if (mbIsWeaponFireWandOpen)
		{
			if (mFireWandShootTimer >= mFireWandStat.ShootInterval)
			{
				for (int i = 0; i < mFireWandStat.Count; ++i)
				{
					GameObject* pFire = static_cast<GameObject*>(mpFireWandObjPool->Get(mPos, mFireWandStat.Damage, mFireWandStat.Speed * mWeaponSpeedCoefficient, mKnockbackValue, mFireWandStat.ShootInterval, mpFireWandObjPool));
					Scene* scene = SceneManager::GetCurrentScene();
					scene->AddWeaponObject(pFire);
				}
				mFireWandShootTimer = 0.0f;
			}
		}

	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void Player::OnCollisionEnter(Collider* other)
	{
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

	void Player::DamageFromMonster(const int damage)
	{
		int actualDamage = std::clamp(damage - mAmour, 1, 100);
		mHp -= actualDamage;
		if (mHp <= 0)
		{
			mHp = 100;
		}
	}

	void Player::WalkComplete()
	{
		/*Missile* pMis = ya::object::Instantiate<Missile>(eColliderLayer::PLAYER_PROJECTTILE);
		pMis->SetPos(mPos);*/
	}


	void Player::IncreaseExp(const int exp)
	{
		mExp += exp;
		if (mExp >= 100)
		{
			mExp = 0;
			++mLevel;
			LevelUpUIManager::GetInstance().PickUpImage();
			UIManager::Pop(eUIType::PLAY_INFO_HUD);
			UIManager::Push(eUIType::PLAY_LEVEL_UP);
		}
	}
	Player::WeaponStat& Player::GetWeaponStat(const eWeaponAndItemTypes type)
	{
		assert(static_cast<UINT>(type) <= static_cast<UINT>(eWeaponAndItemTypes::AXE));
		switch (type)
		{
		case eWeaponAndItemTypes::KNIFE:
			return mKnifeStat;
			break;
		case eWeaponAndItemTypes::FIRE_WAND:
			return mFireWandStat;
			break;
		case eWeaponAndItemTypes::RUNE:
			return mRuneStat;
			break;
		case eWeaponAndItemTypes::AXE:
			return mAxeStat;
			break;
		default:
			assert(false);
			break;
		}

	}
	void Player::IncreaseWeaponStat(const eWeaponAndItemTypes type)
	{
		assert(static_cast<UINT>(type) <= static_cast<UINT>(eWeaponAndItemTypes::AXE));
		if (static_cast<UINT>(type) <= static_cast<UINT>(eWeaponAndItemTypes::AXE))
		{
			unsigned char itemLevel = mPlyerItemLevelStat.ItemLevels[static_cast<UINT>(type)];
			if (itemLevel == 1)
			{
				switch (type)
				{
				case eWeaponAndItemTypes::FIRE_WAND:
					mbIsWeaponFireWandOpen = true;
					mpFireWandObjPool = new WeaponObjectPool<FireWand>(10);
					break;
				case eWeaponAndItemTypes::RUNE:
					mbIsWeaponRuneOpen = true;
					mpRuneObjPool = new WeaponObjectPool<RuneTracer>(5);
					break;
				case eWeaponAndItemTypes::AXE:
					mbIsWeaponAxeOpen = true;
					mpAxeObjPool = new WeaponObjectPool<Axe>(5);
					break;
				default:
					assert(false);
					break;
				}
				return;
			}
			switch (type)
			{
			case eWeaponAndItemTypes::KNIFE:
				switch (itemLevel)
				{
				case 2u:
					// 투사체 1개 더 발사
					++mKnifeStat.Count;
					break;
				case 3u:
					// 투사체 1개 더 발사
					// 기본피해 5 증가
					++mKnifeStat.Count;
					mKnifeStat.Damage += 5;
					break;
				case 4u:
					// 투사체 1개 더 발사
					++mKnifeStat.Count;
					break;
				case 5u:
					// 적 1마리 추가 관통
					++mKnifeStat.PanetratingCount;
					break;
				default:
					assert(false);
					break;
				}
				break;
			case eWeaponAndItemTypes::FIRE_WAND:
				switch (itemLevel)
				{
				case 2u:
					// 기본피해 10 증가
					mFireWandStat.Damage += 10;
					break;
				case 3u:
					// 기본피해 10 증가
					// 투사체 속도 20% 증가
					mFireWandStat.Damage += 10;
					mFireWandStat.Speed *= 1.2f;
					break;
				case 4u:
					// 기본피해 10증가
					mFireWandStat.Damage += 10;
					break;
				case 5u:
					// 기본피해 10증가
					// 투사체 속도 20% 증가
					mFireWandStat.Damage += 10;
					mFireWandStat.Speed *= 1.2f;
					break;
				default:
					assert(false);
					break;
				}
				break;
			case eWeaponAndItemTypes::RUNE:
				switch (itemLevel)
				{
				case 2u:
					// 기본피해 5증가
					// 투사체속도 20% 증가
					mRuneStat.Damage += 5;
					mRuneStat.Speed *= 1.2f;
					break;
				case 3u:
					// 기본피해 5 증가
					// 지속시간 0.3초 증가
					mRuneStat.Damage += 5;
					// TODO : Rune 지속시간 구현해야 함.
					break;
				case 4u:
					// 투사체 1개 추가발사
					++mRuneStat.Count;
					break;
				case 5u:
					// 기본피해 5 증가
					// 투사체 속도 20% 증가
					mRuneStat.Damage += 5;
					mRuneStat.Speed *= 1.2f;
					break;
				default:
					assert(false);
					break;
				}
				break;
			case eWeaponAndItemTypes::AXE:
				switch (itemLevel)
				{
				case 2u:
					// 투사체 1개 추가 발사
					++mAxeStat.Count;
					break;
				case 3u:
					// 기본피해 20 증가
					mAxeStat.Damage += 20;
					break;
				case 4u:
					// 적 2마리 추가 관통
					mAxeStat.PanetratingCount += 2;
					break;
				case 5u:
					// 투사체 1개 추가 발사
					++mAxeStat.Count;
					break;
				default:
					assert(false);
					break;
				}
				break;
			default:
				assert(false);
				break;
			}
		}

	}
}