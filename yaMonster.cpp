#include "yaMonster.h"
#include "yaPlayer.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaWeapon.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaExpGem.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaExpGemObjPool.h"
#include "yaMonsterObjPool.h"
#include "yaApplication.h"
#include "yaCamera.h"
#include "yaKillCounter.h"
#include "yaScoreManager.h"
#include "yaSoundManager.h"
#include "yaSound.h"

namespace ya
{
	Monster::Monster(
		const MonsterCreateInfo& monInfo,
		const std::wstring& imageRightMoveKey,
		const std::wstring& imageLeftMoveKey,
		const std::wstring& imageRightDeathKey,
		const std::wstring& imageLeftDeathKey,
		const std::wstring& imageRightHittedKey,
		const std::wstring& imageLeftHittedKey,


		const std::wstring& imageRightMovePath,
		const std::wstring& imageLeftMovePath,
		const std::wstring& imageRightDeathPath,
		const std::wstring& imageLeftDeathPath,
		const std::wstring& imageRightHittedPath,
		const std::wstring& imageLeftHittedPath,
		ExpGemObjPool* pExpGemObjPool,
		MonsterObjPool<Monster>* pMonsterObjPool
	)
		: GameObject(monInfo.Pos)
		, mpPlayer(monInfo.PtrPlayer)
		, mHP(monInfo.Hp)
		, mDamage(monInfo.Damage)
		, mExp(monInfo.Exp)
		, mSpeed(monInfo.Speed)
		, mPlayerPos(mpPlayer->GetPos())
		, meLookDir(eMonsterLookDir::COUNT)
		, mImageRightMoveKey(imageRightMoveKey)
		, mImageLeftMoveKey(imageLeftMoveKey)
		, mImageRightDeathKey(imageRightDeathKey)
		, mImageLeftDeathKey(imageLeftDeathKey)
		, mImageRightHittedKey(imageRightHittedKey)
		, mImageLeftHittedKey(imageLeftHittedKey)
		, mpRightImage(Resources::Load<Image>(imageRightMoveKey, imageRightMovePath))
		, mpLeftImage(Resources::Load<Image>(imageLeftMoveKey, imageLeftMovePath))
		, mpRightDeathImage(Resources::Load<Image>(imageRightDeathKey, imageRightDeathPath))
		, mpLeftDeathImage(Resources::Load<Image>(imageLeftDeathKey, imageLeftDeathPath))
		, mpRightHittedImage(Resources::Load<Image>(imageRightHittedKey, imageRightHittedPath))
		, mpLeftHittedImage(Resources::Load<Image>(imageLeftHittedKey, imageLeftHittedPath))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(monInfo.AnimMoveSize))
		, mAnimMoveSize(monInfo.AnimMoveSize)
		, mAnimDeathSize(monInfo.AnimDeathSize)
		, mAnimOffset(monInfo.AnimOffset)
		, mAnimImageCount(monInfo.AnimImageCount)
		, mAnimDeathImageCount(monInfo.AnimDeathImageCount)
		, mAnimDuration(monInfo.AnimDuration)
		, mAnimDeathCounter(monInfo.AnimDeathDuration)
		, mAnimHittedCounter(0.0f)
		, mAnimHittedTime(monInfo.AnimDuration* monInfo.AnimImageCount)
		, mbIsDeathFromWeapon(false)
		, mbIsHittedFromWeapon(false)
		, mDisplayWeaponDamage(0)
		, mpExpGemObjPool(pExpGemObjPool)
		, mpMonsterObjPool(pMonsterObjPool)
		, mHwnd(Application::GetInstance().GetWindowData().hwnd)
		, mR(1.0f)
		, mG(1.0f)
		, mB(1.0f)
		, mRecogRange(0.0f)
		, meCurrState(eMonsterState::PATROL)
	{
		assert(mpPlayer != nullptr);
		assert(mHP != 0);
		assert(mDamage != 0);
		assert(mExp != 0);
		assert(std::abs(mSpeed) > FLT_EPSILON);
		assert(mpRightImage != nullptr);
		assert(mpLeftImage != nullptr);
		assert(mpRightDeathImage != nullptr);
		assert(mpLeftDeathImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		assert(mpExpGemObjPool != nullptr);
		assert(mpMonsterObjPool != nullptr);
		
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpCollider->SetColliderLayer(eColliderLayer::MONSTER);
		mpAnimator->CreateAnimation(mImageRightMoveKey, mpRightImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimImageCount, mAnimDuration);
		mpAnimator->CreateAnimation(mImageLeftMoveKey, mpLeftImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimImageCount, mAnimDuration);
		mpAnimator->CreateAnimation(mImageRightDeathKey, mpRightDeathImage, Vector2::ZERO, mAnimDeathSize, mAnimOffset, mAnimDeathImageCount, mAnimDuration);
		mpAnimator->CreateAnimation(mImageLeftDeathKey, mpLeftDeathImage, Vector2::ZERO, mAnimDeathSize, mAnimOffset, mAnimDeathImageCount, mAnimDuration);
		mpAnimator->CreateAnimation(mImageRightHittedKey, mpRightHittedImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimImageCount, mAnimDuration);
		mpAnimator->CreateAnimation(mImageLeftHittedKey, mpLeftHittedImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimImageCount, mAnimDuration);

		mFont.lfHeight = 30;
		mFont.lfWidth = 0;
		mFont.lfEscapement = 0;
		mFont.lfOrientation = 0;
		mFont.lfItalic = 0;
		mFont.lfUnderline = 0;
		mFont.lfStrikeOut = 0;
		mFont.lfCharSet = ARABIC_CHARSET;
		mFont.lfOutPrecision = 0;
		mFont.lfClipPrecision = 0;
		mFont.lfQuality = 0;
		mFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		lstrcpy(mFont.lfFaceName, L"Tekton Pro");
	}

	void Monster::Tick()
	{
		GameObject::Tick();
		assert(mpPlayer != nullptr);

		if (mbIsDeathFromWeapon)
		{
			mAnimDeathCounter -= Time::DeltaTime();
			if (meLookDir == eMonsterLookDir::LEFT)
				{mpAnimator->Play(mImageLeftDeathKey, false);}
			else
				{mpAnimator->Play(mImageRightDeathKey, false);}

			if (mAnimDeathCounter <= 0.0f)
			{
				mpMonsterObjPool->Return(this);
				return;
			}
			return;
		}

		mPlayerPos = mpPlayer->GetPos();
		float diffX = mPos.x - mPlayerPos.x;
		if (diffX < 0.0f)
		{
			meLookDir = eMonsterLookDir::RIGHT;
			if (mbIsHittedFromWeapon)
			{
				CountHitAnimationTimer();
				mpAnimator->Play(mImageRightHittedKey, false);
			}
			else
				{ mpAnimator->Play(mImageRightMoveKey, true); }
		}
		else
		{
			meLookDir = eMonsterLookDir::LEFT;
			if (mbIsHittedFromWeapon)
			{
				CountHitAnimationTimer();
				mpAnimator->Play(mImageLeftHittedKey, false);
			}
			else
				{ mpAnimator->Play(mImageLeftMoveKey, true); }
		}
	}

	void Monster::CountHitAnimationTimer()
	{
		mAnimHittedCounter -= Time::DeltaTime();
		//mR -= 0.002f;
		//mG -= 0.002f;
		//mB -= 0.002f;
		//if (mR < 0.0f || mG < 0.0f || mB < 0.0f)
		//{
		//	mR = 1.0f;
		//	mG = 1.0f;
		//	mB = 1.0f;
		//}
		if (mAnimHittedCounter <= 0.0f)
		{
			mbIsHittedFromWeapon = false;
			mAnimHittedCounter = mAnimHittedTime;
			//mR = 1.0f;
			//mG = 1.0f;
			//mB = 1.0f;
		}
	}

	void Monster::Render(HDC hdc)
	{
		//if (mbIsHittedFromWeapon)
		//{
		//	wchar_t buffer[8];
		//	swprintf_s(buffer, 8, L"%d", mDisplayWeaponDamage);
		//	int len = lstrlenW(buffer);

		//	HFONT hFont = CreateFontIndirect(&mFont);
		//	HFONT hOldFont;
		//	hOldFont = (HFONT)SelectObject(hdc, hFont);

		//	SetBkMode(hdc, TRANSPARENT);
		//	SetTextColor(hdc, RGB(static_cast<int>(mR * 255), static_cast<int>(mG * 255), static_cast<int>(mB * 255)));
		//	TextOutW(hdc, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, buffer, len);

		//	SelectObject(hdc, hOldFont);
		//	DeleteObject(hFont);
		//	ReleaseDC(mHwnd, hdc);
		//}
		GameObject::Render(hdc);
	}

	Monster::~Monster()
	{
	}


	void Monster::OnCollisionEnter(Collider* pCollider)
	{
		switch (pCollider->GetColliderLayer())
		{
		case eColliderLayer::PLAYER_PROJECTTILE:
		{
			Weapon* pWeapon = static_cast<Weapon*>(pCollider->GetOwner());
			SoundManager& sm = SoundManager::GetInstance();
			Sound* pSound = sm.GetSound(sm.ENEMY_HITTED_KEY);
			pSound->Play(false);
			mbIsHittedFromWeapon = true;
			mDisplayWeaponDamage = pWeapon->GetDamage();
			mHP -= mDisplayWeaponDamage;
			if (mHP <= 0)
			{
				mbIsDeathFromWeapon = true;
				PlayScene* pScene = static_cast<PlayScene*>(SceneManager::GetCurrentScene());
				ExpGem* pExpGem = mpExpGemObjPool->Get(mPos, mpPlayer, mExp, mpExpGemObjPool);
				pScene->AddGameObject(pExpGem, eColliderLayer::EXP_JEM);
				mpCollider->SetIsWorking(false);
				mpCollider->SetSize(Vector2::ZERO);
				KillCounter::GetInstance().IncreaseKillCount();
			}
			break;
		}
		default:
			break;
		}
	}
	void Monster::OnCollisionStay(Collider* pCollider)
	{
		if (pCollider->GetColliderLayer() == eColliderLayer::MONSTER)
		{
			if (pCollider->GetSize() == Vector2::ZERO || mpCollider->GetSize() == Vector2::ZERO)
			{
				return;
			}

			Vector2 myCollderSize = mpCollider->GetSize();
			GameObject* pOtherObject = pCollider->GetOwner();
			Vector2 otherColliderSize = pCollider->GetSize();
			Vector2 objPos = pOtherObject->GetPos();

			GameObject* pFixedObject;
			GameObject* pMovingObject;

			//float myLeftTopX = mPos.x - myCollderSize.x / 2;
			//float myRightBottomX = mPos.x + myCollderSize.x / 2;

			//float otherLeftTopX = objPos.x - otherColliderSize.x / 2;
			//float otherRightBottomX = objPos.x + otherColliderSize.x / 2;

			//float pushXLength = 0.0f;

			//if (myLeftTopX <= otherLeftTopX)
			//{
			//	pFixedObject = this;
			//	pMovingObject = pOtherObject;
			//	pushXLength = myRightBottomX - otherLeftTopX;
			//}
			//else
			//{
			//	pFixedObject = pOtherObject;
			//	pMovingObject = this;
			//	pushXLength = otherRightBottomX - myLeftTopX;
			//}

			//pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x + pushXLength * mSpeed * Time::DeltaTime(), pMovingObject->GetPos().y));


			//float myLeftTopY = mPos.y - myCollderSize.y / 2;
			//float myRightBottomY = mPos.y + myCollderSize.y / 2;

			//float otherLeftTopY = objPos.y - otherColliderSize.y / 2;
			//float otherRightBottomY = objPos.y + otherColliderSize.y / 2;

			//// my?? ?????? y?????? other?? ?????? y???????? ???? ??????
			//float pushYlengh = 0.0f;
			//// TODO : ?????? ????????
			//if (myLeftTopY <= otherLeftTopY)
			//{
			//	pFixedObject = this;
			//	pMovingObject = pOtherObject;
			//	//pushYlengh = -(otherLeftTopY - myRightBottomY);
			//	pushYlengh = std::abs(myRightBottomY - otherLeftTopY);
			//}
			//// my?? ?????? y?????? other?? ?????? y???????? ?????? ??????
			//else
			//{
			//	pFixedObject = pOtherObject;
			//	pMovingObject = this;
			//	pushYlengh = std::abs(otherRightBottomY - myLeftTopY);
			//}


			//assert(std::abs(pushXLength) > FLT_EPSILON && std::abs(pushYlengh) > FLT_EPSILON);
			//pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x, pMovingObject->GetPos().y + pushYlengh * mSpeed * Time::DeltaTime()));
			//pMovingObject->SetPos(
			//	Vector2(
			//	pMovingObject->GetPos().x + pushXLength * mSpeed * Time::DeltaTime(), 
			//	pMovingObject->GetPos().y + pushYlengh * mSpeed * Time::DeltaTime()
			//	)
			//);


			// TODO : ??????

			//float myLeft = mPos.x - myCollderSize.x / 2;
			//float myRight = mPos.x + myCollderSize.x / 2;

			//float otherLeft = objPos.x - otherColliderSize.x / 2;
			//float otherRight = objPos.x + otherColliderSize.x / 2;

			//float pushXLength = 0.0f;

			//if (myLeft <= otherLeft)
			//{
			//	pFixedObject = this;
			//	pMovingObject = pOtherObject;
			//	pushXLength = std::abs(myRight - otherLeft);
			//}
			//else
			//{
			//	pFixedObject = pOtherObject;
			//	pMovingObject = this;
			//	pushXLength = std::abs(otherRight - myLeft);
			//}
			//if (std::abs(pushXLength) > FLT_EPSILON)
			//{
			//	pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x + (pushXLength * 0.5f * Time::DeltaTime()), pMovingObject->GetPos().y));
			//}


			//float myTop = mPos.y - myCollderSize.y / 2;
			//float myBot = mPos.y + myCollderSize.y / 2;

			//float otherTop = objPos.y - otherColliderSize.y / 2;
			//float otherBot = objPos.y + otherColliderSize.y / 2;

			//float pushYlengh = 0.0f;
			//// my?? y?????? other?? y???????? ???? ??????
			//if (myTop <= otherTop)
			//{
			//	pFixedObject = this;
			//	pMovingObject = pOtherObject;
			//	//pushYlengh = -(otherLeftTopY - myRightBottomY);
			//	pushYlengh = std::abs(otherTop - myBot);
			//}
			//// my?? ?????? y?????? other?? ?????? y???????? ?????? ??????
			//else
			//{
			//	pFixedObject = pOtherObject;
			//	pMovingObject = this;
			//	pushYlengh = std::abs(otherBot - myTop);
			//}


			//if (std::abs(pushYlengh) > FLT_EPSILON)
			//{
			//	pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x, pMovingObject->GetPos().y + (pushYlengh * Time::DeltaTime())));
			//}
			//pMovingObject->SetPos(
			//	Vector2(
			//	pMovingObject->GetPos().x + pushXLength * mSpeed * Time::DeltaTime(), 
			//	pMovingObject->GetPos().y + pushYlengh * mSpeed * Time::DeltaTime()
			//	)
			//);
			
			float myLeft = mPos.x - myCollderSize.x / 2;
			float myRight = mPos.x + myCollderSize.x / 2;

			float otherLeft = objPos.x - otherColliderSize.x / 2;
			float otherRight = objPos.x + otherColliderSize.x / 2;

			float pushXLength = 0.0f;

			if (meLookDir == eMonsterLookDir::LEFT)
			{
				if (myLeft <= otherLeft)
				{
					pFixedObject = this;
					pMovingObject = pOtherObject;
					pushXLength = std::abs(myRight - otherLeft);
				}
				else
				{
					pFixedObject = pOtherObject;
					pMovingObject = this;
					pushXLength = std::abs(otherRight - myLeft);
				}
			}
			else
			{
				if (myLeft <= otherLeft)
				{
					pFixedObject = pOtherObject;
					pMovingObject = this;
					pushXLength = -std::abs(myRight - otherLeft);
				}
				else
				{
					pFixedObject = this;
					pMovingObject = pOtherObject;
					pushXLength = -std::abs(otherRight - myLeft);
				}
			}
			if (std::abs(pushXLength) > FLT_EPSILON)
			{
				pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x + (pushXLength * Time::DeltaTime()), pMovingObject->GetPos().y));
			}


			float myTop = mPos.y - myCollderSize.y / 2;
			float myBot = mPos.y + myCollderSize.y / 2;

			float otherTop = objPos.y - otherColliderSize.y / 2;
			float otherBot = objPos.y + otherColliderSize.y / 2;

			float pushYlengh = 0.0f;
			// my?? y?????? other?? y???????? ???? ??????
			if (myTop <= otherTop)
			{
				pFixedObject = this;
				pMovingObject = pOtherObject;
				//pushYlengh = -(otherLeftTopY - myRightBottomY);
				pushYlengh = std::abs(otherTop - myBot);
			}
			// my?? ?????? y?????? other?? ?????? y???????? ?????? ??????
			else
			{
				pFixedObject = pOtherObject;
				pMovingObject = this;
				pushYlengh = std::abs(otherBot - myTop);
			}


			if (std::abs(pushYlengh) > FLT_EPSILON)
			{
				pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x, pMovingObject->GetPos().y + (pushYlengh * Time::DeltaTime())));
			}
		}
	}
	void Monster::OnCollisionExit(Collider* pCollider)
	{
	}
}