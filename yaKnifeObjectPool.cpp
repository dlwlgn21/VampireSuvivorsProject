#include "yaKnifeObjectPool.h"

namespace ya
{
	KnifeObjectPool::KnifeObjectPool(UINT maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{
	}

	Knife* KnifeObjectPool::Get(Vector2 spwanPos, int damage, float speed, float knockBackValue, float shootInterval, eKnifeDirection dir, KnifeObjectPool* pPool)
	{
		if (mQ.empty())
		{
			return new Knife(spwanPos, damage, speed, knockBackValue, shootInterval, dir, pPool);
		}
		Knife* pKnife = mQ.front();
		pKnife->Initialize(spwanPos, dir);
		pKnife->SetActive(true);
		mQ.pop();
		return pKnife;
	}
	void KnifeObjectPool::Return(Knife* pKnife)
	{
		if (mQ.size() >= mMaxPoolSize)
		{
			/* CAN NOT ENTER THIS STATEMENT */
			assert(false);
			return;
		}
		mQ.push(pKnife);
	}
	UINT KnifeObjectPool::GetFreeObjectCount() const
	{
		return static_cast<UINT>(mQ.size());
	}
	UINT KnifeObjectPool::GetMaxFreeObjectCount() const
	{
		return mMaxPoolSize;
	}
}