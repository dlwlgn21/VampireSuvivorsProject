#define LEGNTH_OF_LEFT_PLAYER_DISTANCE (200.0f)
#define INITIAL_Y_SPAWN_POS (-300.0f)
#define MUDMAN_INITIAL_SPAWN_COUNT (10)

#include "yaMonsterSpawner.h"
#include "yaTime.h"
#include "yaExpGemObjPool.h"
#include "yaMonsterObjPool.h"
#include "yaMonster.h"
#include "yaMudman.h"
#include "yaPlayer.h"
#include "yaMonsterFactory.h"


namespace ya
{
	void MonsterSpawner::Tick()
	{
		mAccumTimer += Time::DeltaTime();
		setSpawnPos();
		if (!mbIsMudmanEmergence)
		{
			if (mAccumTimer >= MUDMAN_EMERGENCE_SECOND)
			{
				spawnMonsters(eMonsterEmegernceSecquence::MUDMAN);
				mbIsMudmanEmergence = true;
			}
		}
	}

	void MonsterSpawner::ExitScene()
	{
		mAccumTimer = 0.0f;
		mbIsMudmanEmergence = false;
		mbIsMedusaHeadEmergence = false;
		mbIsGreenGhostEmergence = false;
		mpPlayer = nullptr;
		mpExpObjPool = nullptr;
		mMonsterObjectPools.clear();
		mMonsterObjectPools.reserve(static_cast<UINT>(eMonsterEmegernceSecquence::COUNT));
	}

	void MonsterSpawner::spawnMonsters(eMonsterEmegernceSecquence eMonsterEmergenceType)
	{
		assert(static_cast<UINT>(eMonsterEmergenceType) < static_cast<UINT>(eMonsterEmegernceSecquence::COUNT));
		MonsterObjPool<Monster>* pPool = mMonsterObjectPools[static_cast<UINT>(eMonsterEmergenceType)];

		switch (eMonsterEmergenceType)
		{
		case ya::eMonsterEmegernceSecquence::MUDMAN:
		{
			UINT half = static_cast<UINT>(MUDMAN_INITIAL_SPAWN_COUNT / 2);
			int j = MUDMAN_INITIAL_SPAWN_COUNT;
			for (UINT i = 0; i < MUDMAN_INITIAL_SPAWN_COUNT; ++i)
			{
				if (i < half)
				{
					MonsterFactory::CreateMonster(eMonsterType::MUDMAN, Vector2(mLeftSpawanPos.x, INITIAL_Y_SPAWN_POS + (i * 70.0f)), mpPlayer, mpExpObjPool, pPool);
				}
				else
				{
					MonsterFactory::CreateMonster(eMonsterType::MUDMAN, Vector2(mRightSpawnPos.x, INITIAL_Y_SPAWN_POS + (j * 70.0f)), mpPlayer, mpExpObjPool, pPool);
				}
				--j;
			}
			break;
		}
		case ya::eMonsterEmegernceSecquence::MEDUSA_HEAD:
			break;
		case ya::eMonsterEmegernceSecquence::GREEN_GHOST:
			break;
		case ya::eMonsterEmegernceSecquence::COUNT:
			assert(false);
			break;
		default:
			assert(false);
			break;
		}
	}

	void MonsterSpawner::setSpawnPos()
	{
		float leftXSpawnPos = mpPlayer->GetPos().x - LEGNTH_OF_LEFT_PLAYER_DISTANCE;
		float rightXSpawnPos = -leftXSpawnPos;
		mLeftSpawanPos.x = leftXSpawnPos;
		mRightSpawnPos.x = rightXSpawnPos;
	}

	void MonsterSpawner::SetObjectsAndSpawnPos(Player* pPlayer, ExpGemObjPool* pExpObjPool, MonsterObjPool<Monster>* pMonsterObjPool)
	{
		assert(pPlayer != nullptr);
		assert(pExpObjPool != nullptr);
		assert(pMonsterObjPool != nullptr);
		mpPlayer = pPlayer;
		mpExpObjPool = pExpObjPool;
		mMonsterObjectPools.push_back(pMonsterObjPool);

	}
	void MonsterSpawner::AddMonsterObjectPool(MonsterObjPool<Monster>* pMonsterObjPool)
	{
		assert(pMonsterObjPool != nullptr);
		mMonsterObjectPools.push_back(pMonsterObjPool);
	}
}