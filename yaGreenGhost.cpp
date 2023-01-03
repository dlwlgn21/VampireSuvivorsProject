#include "yaGreenGhost.h"
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



namespace ya
{
	GreenGhost::GreenGhost(
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
	{
	}

	void GreenGhost::Tick()
	{
		Monster::Tick();

		if (!mbIsDeathFromWeapon)
		{
			switch (meCurrState)
			{
			case eMonsterState::PATROL:
			{
				Vector2 disToPlyerVector = GetVectorToPlayer();
				float distance = disToPlyerVector.GetLength();
				if (distance < mRecogRange)
				{
					meCurrState = eMonsterState::TRACE;
				}
				else
				{
					if (distance > 3000.0f)
					{
						meCurrState = eMonsterState::TRACE;
						break;
					}

					if (meLookDir == eMonsterLookDir::LEFT)
					{
						mPos.x -= mSpeed * Time::DeltaTime();
					}
					else
					{
						mPos.x += mSpeed * Time::DeltaTime();
					}
				}
				break;
			}
			case eMonsterState::TRACE:
			{
				Vector2 monDir = GetVectorToPlayer();
				monDir.Normalize();
				mPos.x += monDir.x * mSpeed * Time::DeltaTime();
				mPos.y += monDir.y * mSpeed * Time::DeltaTime();
				break;
			}
			case eMonsterState::COUNT:
				assert(false);
				break;
			default:
				assert(false);
				break;
			}
		}
	}
	void GreenGhost::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}
}