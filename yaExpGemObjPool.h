#pragma once
#include "Common.h"

namespace ya
{
	class ExpGem;
	class Player;
	class ExpGemObjPool
	{
	public:
		ExpGemObjPool(UINT maxPoolSize);
		ExpGemObjPool(const ExpGemObjPool& other) = delete;
		ExpGemObjPool& operator=(const ExpGemObjPool& other) = delete;


		~ExpGemObjPool();
		void Initialize();
		ExpGem* Get(Vector2 pos, Player* pPlayer, int exp, ExpGemObjPool* pPool);
		void Return(ExpGem* ptr);
		UINT GetFreeObjectCount() const;
		UINT GetMaxFreeObjectCount() const;

	private:
		UINT mMaxPoolSize;
		std::queue<ExpGem*> mQ;
	};
}


