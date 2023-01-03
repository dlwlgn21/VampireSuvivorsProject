#pragma once
#include "Common.h"

namespace ya
{
	enum class eMonsterEmegernceSecquence
	{
		MUDMAN,
		MEDUSA_HEAD,
		GREEN_GHOST,
		COUNT
	};
	class Player;
	class ExpGem;
	class ExpGemObjPool;
	class Monster;
	template<typename T> class MonsterObjPool;
	class MonsterSpawner final
	{
	public:
		static MonsterSpawner& GetInstance()
		{
			static MonsterSpawner spawner;
			return spawner;
		}
		MonsterSpawner(const MonsterSpawner& other) = delete;
		MonsterSpawner& operator=(const MonsterSpawner& other) = delete;

		void Tick();
		void ExitScene();
		void SetObjectsAndSpawnPos(Player* pPlayer, ExpGemObjPool* pExpObjPool, MonsterObjPool<Monster>* pMonsterObjPool);
		void AddMonsterObjectPool(MonsterObjPool<Monster>* pMonsterObjPool);
		__forceinline float GetAccumTime() const { return mAccumTimer; }



	private:
		MonsterSpawner()
			: MUDMAN_EMERGENCE_SECOND(1.0f)
			, MEDUSA_HEAD_EMERGENCE_SECOND(60.0f)
			, GREEN_GHOST_EMERGENCE_SECOND(90.0f)
			, mAccumTimer(0.0f)
			, mLeftSpawanPos(Vector2::ZERO)
			, mRightSpawnPos(Vector2::ZERO)
			, mpPlayer(nullptr)
			, mpExpObjPool(nullptr)
			, mbIsMudmanEmergence(false)
		    , mbIsMedusaHeadEmergence(false)
		    , mbIsGreenGhostEmergence(false)
		{
			mMonsterObjectPools.reserve(static_cast<UINT>(eMonsterEmegernceSecquence::COUNT));
		}
		~MonsterSpawner() = default;
		void spawnMonsters(eMonsterEmegernceSecquence eMonsterEmergenceType);
		__forceinline void setSpawnPos();

	private:
		const float MUDMAN_EMERGENCE_SECOND;
		const float MEDUSA_HEAD_EMERGENCE_SECOND;
		const float GREEN_GHOST_EMERGENCE_SECOND;
		float mAccumTimer;
		Vector2 mLeftSpawanPos;
		Vector2 mRightSpawnPos;
		Player* mpPlayer;
		ExpGemObjPool* mpExpObjPool;
		std::vector<MonsterObjPool<Monster>*> mMonsterObjectPools;
		bool mbIsMudmanEmergence;
		bool mbIsMedusaHeadEmergence;
		bool mbIsGreenGhostEmergence;
	};

}

