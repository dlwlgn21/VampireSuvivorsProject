#pragma once
#include "Common.h"
#include "yaWeapon.h"
#include "yaCollider.h"

namespace ya
{
	template<typename T>
	class WeaponObjectPool final
	{
	public:
		WeaponObjectPool(UINT maxPoolSize);
		WeaponObjectPool(const WeaponObjectPool& other) = delete;
		WeaponObjectPool& operator=(const WeaponObjectPool& other) = delete;
		~WeaponObjectPool();

		T* Get(Vector2 spwanPos, int damage, int penetratingCount, float speed, float knockBackValue, float shootInterval, WeaponObjectPool* pPool);
		void Return(T* pKnife);
		UINT GetFreeObjectCount() const;
		UINT GetMaxFreeObjectCount() const;

	private:
		UINT mMaxPoolSize;
		std::queue<T*> mQ;

	private:
	};

	template<typename T>
	WeaponObjectPool<T>::WeaponObjectPool(UINT maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{
	}

	template<typename T>
	WeaponObjectPool<T>::~WeaponObjectPool()
	{
		while (!mQ.empty())
		{
			T* ptr = mQ.front();
			if (ptr != nullptr)
				{ delete ptr; }
			mQ.pop();
		}
	}

	template<typename T>
	T* WeaponObjectPool<T>::Get(Vector2 spwanPos, int damage, int penetratingCount, float speed, float knockBackValue, float shootInterval, WeaponObjectPool* pPool)
	{
		if (mQ.empty())
		{
			return new T(spwanPos, damage, penetratingCount, speed, knockBackValue, shootInterval, pPool);
		}
		T* ptr = mQ.front();
		ptr->Initialize(spwanPos);
		ptr->SetActive(true);
		Collider* pCollider = ptr->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
		assert(pCollider != nullptr);
		pCollider->SetIsWorking(true);
		mQ.pop();
		return ptr;
	}
	template<typename T>
	void WeaponObjectPool<T>::Return(T* ptr)
	{
		if (mQ.size() >= mMaxPoolSize)
		{
			/* CAN NOT ENTER THIS STATEMENT */
			assert(false);
			return;
		}
		ptr->SetActive(false);
		Collider* pCollider = ptr->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
		assert(pCollider != nullptr);
		pCollider->SetIsWorking(false);
		mQ.push(ptr);
	}
	template<typename T>
	UINT WeaponObjectPool<T>::GetFreeObjectCount() const
	{
		return mQ.size();
	}

	template<typename T>
	UINT WeaponObjectPool<T>::GetMaxFreeObjectCount() const
	{
		return mMaxPoolSize;
	}


}