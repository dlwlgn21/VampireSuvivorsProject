#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaPlayer.h"
#include "yaMudman.h"
#include "yaGreenGhost.h"
#include "yaMedusaHead.h"
#include "yaCollider.h"

namespace ya
{
	class Monster;
	class Mudman;
	template<typename T>
	class MonsterObjPool final
	{
	public:
		MonsterObjPool(UINT maxPoolSize);
		MonsterObjPool(const MonsterObjPool& other) = delete;
		MonsterObjPool& operator=(const MonsterObjPool& other) = delete;

		~MonsterObjPool();

		void Initialize();

		Monster* Get(
			const eMonsterType eMonsterType,
			const MonsterCreateInfo& monInfo,
			const std::wstring& imageRightMoveKey,
			const std::wstring& imageLeftMoveKey,
			const std::wstring& imageRightDeathKey,
			const std::wstring& imageLeftDeathKey,
			const std::wstring& imageRightHittedKey,
			const std::wstring& imageLeftHittedKey,


			const std::wstring& imageRightMovePath,
			const std::wstring& imageLeftMovePath,
			const std::wstring& imageRightDeathPath,
			const std::wstring& imageLeftDeathPath,
			const std::wstring& imageRightHittedPath,
			const std::wstring& imageLeftHittedPath,
			ExpGemObjPool* pExpGemObjPool,
			MonsterObjPool<Monster>* pMonsterObjPool
		);
		void Return(Monster* ptr);
		UINT GetFreeObjectCount() const;
		UINT GetMaxFreeObjectCount() const;

	private:
		UINT mMaxPoolSize;
		std::queue<T*> mQ;
	};


	template<typename T>
	MonsterObjPool<T>::MonsterObjPool(UINT maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{
	}

	template<typename T>
	MonsterObjPool<T>::~MonsterObjPool()
	{
		while (!mQ.empty())
		{
			delete mQ.front();
			mQ.pop();
		}
	}

	template<typename T>
	void MonsterObjPool<T>::Initialize()
	{
		while (!mQ.empty())
		{
			delete mQ.front();
			mQ.pop();
		}
	}


	template<typename T>
	Monster* MonsterObjPool<T>::Get(
		const eMonsterType eType,
		const MonsterCreateInfo& monInfo,
		const std::wstring& imageRightMoveKey,
		const std::wstring& imageLeftMoveKey,
		const std::wstring& imageRightDeathKey,
		const std::wstring& imageLeftDeathKey,
		const std::wstring& imageRightHittedKey,
		const std::wstring& imageLeftHittedKey,


		const std::wstring& imageRightMovePath,
		const std::wstring& imageLeftMovePath,
		const std::wstring& imageRightDeathPath,
		const std::wstring& imageLeftDeathPath,
		const std::wstring& imageRightHittedPath,
		const std::wstring& imageLeftHittedPath,
		ExpGemObjPool* pExpGemObjPool,
		MonsterObjPool<Monster>* pMonsterObjPool
	)
	{
		if (mQ.empty())
		{
			T* pMonster;
			switch (eType)
			{
			case eMonsterType::MUDMAN:
			{
				pMonster = new Mudman(
					monInfo, 
					imageRightMoveKey, imageLeftMoveKey, 
					imageRightDeathKey, imageLeftDeathKey,
					imageRightHittedKey, imageLeftHittedKey,
					imageRightMovePath, imageLeftMovePath, 
					imageRightDeathPath, imageLeftDeathPath, 
					imageRightHittedPath, imageLeftHittedPath,
					pExpGemObjPool, pMonsterObjPool);
				return pMonster;
				break;
			}
			case eMonsterType::GREEN_GHOST:
			{
				pMonster = new GreenGhost(
					monInfo,
					imageRightMoveKey, imageLeftMoveKey,
					imageRightDeathKey, imageLeftDeathKey,
					imageRightHittedKey, imageLeftHittedKey,
					imageRightMovePath, imageLeftMovePath,
					imageRightDeathPath, imageLeftDeathPath,
					imageRightHittedPath, imageLeftHittedPath,
					pExpGemObjPool, pMonsterObjPool);
				return pMonster;
				break;
			}
			case eMonsterType::MEDUSA_HEAD:
			{
				pMonster = new MedusaHead(
					monInfo,
					imageRightMoveKey, imageLeftMoveKey,
					imageRightDeathKey, imageLeftDeathKey,
					imageRightHittedKey, imageLeftHittedKey,
					imageRightMovePath, imageLeftMovePath,
					imageRightDeathPath, imageLeftDeathPath,
					imageRightHittedPath, imageLeftHittedPath,
					pExpGemObjPool, pMonsterObjPool);
				return pMonster;
				break;
			}
			default:
				assert(false);
				return nullptr;
				break;
			}
		}
		Monster* pRet = mQ.front();
		pRet->SetPos(monInfo.Pos);
		Collider* pCollider = pRet->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
		assert(pCollider != nullptr);
		pCollider->SetSize(pRet->GetSize());
		pCollider->SetIsWorking(true);
		pRet->SetActive(true);
		mQ.pop();
		return pRet;
	}

	template<typename T>
	void MonsterObjPool<T>::Return(Monster* ptr)
	{
		if (mQ.size() >= mMaxPoolSize)
		{
			delete ptr;
			return;
		}
		ptr->SetActive(false);
		mQ.push(ptr);
	}

	template<typename T>
	UINT MonsterObjPool<T>::GetFreeObjectCount() const
	{
		return mQ.size();
	}

	template<typename T>
	UINT MonsterObjPool<T>::GetMaxFreeObjectCount() const
	{
		return mMaxPoolSize;
	}
}

