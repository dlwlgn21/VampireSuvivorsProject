#include "yaMedusaHead.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"
#include "yaPlayer.h"
#include "yaTime.h"
#include "yaWeapon.h"
#include "yaExpGem.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaExpGemObjPool.h"
#include "yaMonsterObjPool.h"

namespace ya
{
	MedusaHead::MedusaHead(
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
		: Monster(
			monInfo,
			imageRightMoveKey, imageLeftMoveKey,
			imageRightDeathKey, imageLeftDeathKey,
			imageRightHittedKey, imageLeftHittedKey,
			imageRightMovePath, imageLeftMovePath,
			imageRightDeathPath, imageLeftDeathPath,
			imageRightHittedPath, imageLeftHittedPath,
			pExpGemObjPool, pMonsterObjPool)
		, mAccumVal(0.0f)
	{
		mPlayerPos = mpPlayer->GetPos();
		float diffX = mPos.x - mPlayerPos.x;
		if (diffX < 0.0f)
		{
			meLookDir = eMonsterLookDir::RIGHT;
			mpAnimator->Play(mImageRightMoveKey, true);
		}
		else
		{
			meLookDir = eMonsterLookDir::LEFT;
			mpAnimator->Play(mImageLeftMoveKey, true);
		}
	}

	void MedusaHead::Tick()
	{
		GameObject::Tick();
		if (mbIsDeathFromWeapon)
		{
			mAnimDeathCounter -= Time::DeltaTime();
			if (meLookDir == eMonsterLookDir::LEFT)
			{
				mpAnimator->Play(mImageLeftDeathKey, false);
			}
			else
			{
				mpAnimator->Play(mImageRightDeathKey, false);
			}

			if (mAnimDeathCounter <= 0.0f)
			{
				mpMonsterObjPool->Return(this);
				return;
			}
			return;
		}

		
		if (mbIsHittedFromWeapon)
		{
			CountHitAnimationTimer();
			if (meLookDir == eMonsterLookDir::LEFT)
			{
				mpAnimator->Play(mImageLeftHittedKey, false);
			}
			else
			{
				mpAnimator->Play(mImageRightHittedKey, false);
			}
		}
		mAccumVal += 0.1f;
		if (!mbIsDeathFromWeapon)
		{
			Vector2 distanceVector = GetVectorToPlayer();
			float distance = distanceVector.GetLength();
			if (distance > 3000.0f)
			{
				mpMonsterObjPool->Return(this);
				return;
			}

			float sinVal = sinf(mAccumVal);
			if (meLookDir == eMonsterLookDir::LEFT)
			{
				mPos.x -= mSpeed * Time::DeltaTime();
				mPos.y += sinVal * mSpeed * Time::DeltaTime();
			}
			else
			{
				mPos.x += mSpeed * Time::DeltaTime();
				mPos.y += sinVal * mSpeed * Time::DeltaTime();
			}
		}
	}
	void MedusaHead::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}
}