constexpr float LEGNTH_OF_LEFT_PLAYER_DISTANCE = 1500.0f;
constexpr float INITIAL_Y_SPAWN_POS = -300.0f;
constexpr UINT MUDMAN_INITIAL_SPAWN_COUNT = 15;
constexpr UINT GREEN_GHOST_INITIAL_SPAWN_COUNT = 15;
constexpr UINT MEDUSA_HEAD_INITIAL_SPAWN_COUNT = 10;

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
				spawnMonsters(eMonsterEmegernceSecquence::MUDMAN, MUDMAN_INITIAL_SPAWN_COUNT);
				mbIsMudmanEmergence = true;
			}
		}
		if (mbIsMudmanEmergence)
		{
			mMudmanTimer += Time::DeltaTime();
			if (mMudmanTimer >= mMudmanRespawnTime)
			{
				spawnMonsters(eMonsterEmegernceSecquence::MUDMAN, MUDMAN_INITIAL_SPAWN_COUNT / 3);
				mMudmanTimer = 0.0f;
			}
		}

		if (!mbIsGreenGhostEmergence)
		{
			if (mAccumTimer >= GREEN_GHOST_EMERGENCE_SECOND)
			{
				spawnMonsters(eMonsterEmegernceSecquence::GREEN_GHOST, GREEN_GHOST_INITIAL_SPAWN_COUNT);
				mbIsGreenGhostEmergence = true;
			}
		}

		if (mbIsGreenGhostEmergence)
		{
			mGreenGhostTimer += Time::DeltaTime();
			if (mGreenGhostTimer >= mGreenGhostRespawnTime)
			{
				spawnMonsters(eMonsterEmegernceSecquence::GREEN_GHOST, GREEN_GHOST_INITIAL_SPAWN_COUNT / 3);
				mGreenGhostTimer = 0.0f;
			}
		}

		if (!mbIsMedusaHeadEmergence)
		{
			if (mAccumTimer >= MEDUSA_HEAD_EMERGENCE_SECOND)
			{
				spawnMonsters(eMonsterEmegernceSecquence::MEDUSA_HEAD, MEDUSA_HEAD_INITIAL_SPAWN_COUNT);
				mbIsMedusaHeadEmergence = true;
			}
		}

		if (mbIsMedusaHeadEmergence)
		{
			mMedusaHeadTimer += Time::DeltaTime();
			if (mMedusaHeadTimer >= mMedusaHeadRespawnTime)
			{
				spawnMonsters(eMonsterEmegernceSecquence::MEDUSA_HEAD, MEDUSA_HEAD_INITIAL_SPAWN_COUNT / 3);
				mMedusaHeadTimer = 0.0f;
			}
		}
		
	}

	void MonsterSpawner::Initialize()
	{
		mAccumTimer = 0.0f;
		mMedusaHeadTimer = 0.0f;
		mbIsMudmanEmergence = false;
		mbIsMedusaHeadEmergence = false;
		mbIsGreenGhostEmergence = false;
		mpPlayer = nullptr;
		mpExpObjPool = nullptr;
		mMonsterObjectPools.clear();
		mMonsterObjectPools.reserve(static_cast<UINT>(eMonsterEmegernceSecquence::COUNT));
	}

	void MonsterSpawner::spawnMonsters(eMonsterEmegernceSecquence eMonsterEmergenceType, UINT monsterCount)
	{
		assert(static_cast<UINT>(eMonsterEmergenceType) < static_cast<UINT>(eMonsterEmegernceSecquence::COUNT));
		MonsterObjPool<Monster>* pPool = mMonsterObjectPools[static_cast<UINT>(eMonsterEmergenceType)];

		switch (eMonsterEmergenceType)
		{
		case ya::eMonsterEmegernceSecquence::MUDMAN:
		{
			UINT half = static_cast<UINT>(monsterCount / 2);
			int j = monsterCount;
			for (UINT i = 0; i < monsterCount; ++i)
			{
				if (i < half)
				{
					MonsterFactory::CreateMonster(eMonsterType::MUDMAN, Vector2(mLeftSpawanPos.x, INITIAL_Y_SPAWN_POS + (i * 75.0f)), mpPlayer, mpExpObjPool, pPool);
				}
				else
				{
					MonsterFactory::CreateMonster(eMonsterType::MUDMAN, Vector2(mRightSpawnPos.x, INITIAL_Y_SPAWN_POS + (j * 75.0f)), mpPlayer, mpExpObjPool, pPool);
				}
				--j;
			}
			break;
		}
		case ya::eMonsterEmegernceSecquence::GREEN_GHOST:
		{
			UINT half = static_cast<UINT>(monsterCount / 2);
			int j = monsterCount;
			for (UINT i = 0; i < monsterCount; ++i)
			{
				if (i < half)
				{
					MonsterFactory::CreateMonster(eMonsterType::GREEN_GHOST, Vector2(mLeftSpawanPos.x, INITIAL_Y_SPAWN_POS + (i * 75.0f)), mpPlayer, mpExpObjPool, pPool);
				}
				else
				{
					MonsterFactory::CreateMonster(eMonsterType::GREEN_GHOST, Vector2(mRightSpawnPos.x, INITIAL_Y_SPAWN_POS + (j * 75.0f)), mpPlayer, mpExpObjPool, pPool);
				}
				--j;
			}
			break;
		}
		case ya::eMonsterEmegernceSecquence::MEDUSA_HEAD:
		{
			UINT half = static_cast<UINT>(monsterCount / 2);
			int j = monsterCount;
			for (UINT i = 0; i < monsterCount; ++i)
			{
				if (i < half)
				{
					MonsterFactory::CreateMonster(eMonsterType::MEDUSA_HEAD, Vector2(mLeftSpawanPos.x, INITIAL_Y_SPAWN_POS + (i * 150.0f)), mpPlayer, mpExpObjPool, pPool);
				}
				else
				{
					MonsterFactory::CreateMonster(eMonsterType::MEDUSA_HEAD, Vector2(mRightSpawnPos.x, INITIAL_Y_SPAWN_POS + (j * 150.0f)), mpPlayer, mpExpObjPool, pPool);
				}
				--j;
			}
			break;
		}
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
		float rightXSpawnPos = mpPlayer->GetPos().x + LEGNTH_OF_LEFT_PLAYER_DISTANCE;
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