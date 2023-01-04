#include "yaExpGemObjPool.h"
#include "yaPlayer.h"
#include "yaExpGem.h"
#include "yaCollider.h"

namespace ya
{
	ExpGemObjPool::ExpGemObjPool(UINT maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{
	}
	ExpGemObjPool::~ExpGemObjPool()
	{
		while (!mQ.empty())
		{
			delete mQ.front();
			mQ.pop();
		}
	}
	void ExpGemObjPool::Initialize()
	{
		while (!mQ.empty())
		{
			delete mQ.front();
			mQ.pop();
		}
	}

	ExpGem* ExpGemObjPool::Get(Vector2 pos, Player* pPlayer, int exp, ExpGemObjPool* pPool)
	{
		if (mQ.empty())
		{
			return new ExpGem(pos, pPlayer, exp, pPool);
		}
		ExpGem* pRet = mQ.front();
		pRet->SetPos(pos);
		pRet->SetActive(true);
		Collider* pCollider = pRet->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
		assert(pCollider != nullptr);
		pCollider->SetIsWorking(false);
		mQ.pop();
		return pRet;
	}
	void ExpGemObjPool::Return(ExpGem* pGem)
	{
		if (mQ.size() >= mMaxPoolSize)
		{
			assert(false);
			delete pGem;
			return;
		}
		pGem->SetActive(false);
		Collider* pCollider = pGem->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
		assert(pCollider != nullptr);
		pCollider->SetIsWorking(false);
		mQ.push(pGem);
	}
	UINT ExpGemObjPool::GetFreeObjectCount() const
	{
		return static_cast<UINT>(mQ.size());
	}
	UINT ExpGemObjPool::GetMaxFreeObjectCount() const
	{
		return static_cast<UINT>(mMaxPoolSize);
	}
}