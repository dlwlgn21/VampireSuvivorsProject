#pragma once
#include "Common.h"

namespace ya
{

	class Monster;
	class Player;
	class ExpGemObjPool;
	template<typename T> class MonsterObjPool;
	class MonsterFactory final
	{
	public:
		static Monster* CreateMonster(eMonsterType eType, Vector2 pos, Player* pPlayer, ExpGemObjPool* pExpGemObejctPool, MonsterObjPool<Monster>* pMonsterObjPool);
	private:
		MonsterFactory() = delete;
		~MonsterFactory() = delete;
	};
}

