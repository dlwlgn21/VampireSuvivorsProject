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

		const std::wstring& imageRightMovePath,
		const std::wstring& imageLeftMovePath,
		const std::wstring& imageRightDeathPath,
		const std::wstring& imageLeftDeathPath,
		ExpGemObjPool* pExpGemObjPool,
		MonsterObjPool<Monster>* pMonsterObjPool
	)
		: Monster(monInfo, imageRightMoveKey, imageLeftMoveKey, imageRightDeathKey, imageLeftDeathKey,
			imageRightMovePath, imageLeftMovePath, imageRightDeathPath, imageLeftDeathPath, pExpGemObjPool, pMonsterObjPool)
	{
	}

	void GreenGhost::Tick()
	{
		Monster::Tick();
		if (!mbIsDeathFromWeapon)
		{
			float diffX = mPos.x - mpPlayer->GetPos().x;
			if (diffX < 0.0f)
			{
				mpAnimator->Play(mImageRightMoveKey, true);
			}
			else
			{
				mpAnimator->Play(mImageLeftMoveKey, true);
			}
			Vector2 monDir = GetVectorToPlayer();
			monDir.Normalize();
			mPos.x += monDir.x * mSpeed * Time::DeltaTime();
			mPos.y += monDir.y * mSpeed * Time::DeltaTime();
		}
	}
	void GreenGhost::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}