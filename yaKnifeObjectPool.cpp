#include "yaKnifeObjectPool.h"
#include "yaCollider.h"
namespace ya
{
	KnifeObjectPool::KnifeObjectPool(UINT maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{
	}

	KnifeObjectPool::~KnifeObjectPool()
	{
		while (!mQ.empty())
		{
			Knife* pKnife = mQ.front();
			if (pKnife != nullptr)
			{
				delete pKnife;
			}
			mQ.pop();
		}
	}

	Knife* KnifeObjectPool::Get(Vector2 spwanPos, int damage, int penetratingCount, float speed, float knockBackValue, float shootInterval, eKnifeDirection dir, KnifeObjectPool* pPool)
	{
		if (mQ.empty())
		{
			return new Knife(spwanPos, damage, penetratingCount, speed, knockBackValue, shootInterval, dir, pPool);
		}
		Knife* pKnife = mQ.front();
		pKnife->Initialize(spwanPos, dir);

		pKnife->SetActive(true);
		Collider* pCollider = pKnife->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
		assert(pCollider != nullptr);
		pCollider->SetIsWorking(true);
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
		pKnife->SetActive(false);
		Collider* pCollider = pKnife->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
		assert(pCollider != nullptr);
		pCollider->SetIsWorking(false);
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