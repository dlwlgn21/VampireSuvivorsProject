#pragma once
#include "Common.h"
#include "yaKnife.h"

namespace ya
{
	class KnifeObjectPool final
	{
	public:
		KnifeObjectPool(UINT maxPoolSize);
		~KnifeObjectPool();
		KnifeObjectPool(const KnifeObjectPool& other) = delete;
		KnifeObjectPool& operator=(const KnifeObjectPool& other) = delete;

		Knife* Get(Vector2 spwanPos, int damage, int penetratingCount, float speed, float knockBackValue, float shootInterval, eKnifeDirection dir, KnifeObjectPool* pPool);
		void Return(Knife* pKnife);
		UINT GetFreeObjectCount() const;
		UINT GetMaxFreeObjectCount() const;

	private:
		UINT mMaxPoolSize;
		std::queue<Knife*> mQ;
	};
}

