#pragma once
#include "Common.h"
#include "yaWeapon.h"

namespace ya
{
	template<typename T>
	class WeaponObjectPool final
	{
	public:
		WeaponObjectPool();
		WeaponObjectPool(const WeaponObjectPool& other) = delete;
		WeaponObjectPool& operator=(const WeaponObjectPool& other) = delete;
		~WeaponObjectPool() = default;

		T* Get(Vector2 spwanPos, int damage, float speed, float knockBackValue, float shootInterval, WeaponObjectPool* pPool);
		void Return(T* pKnife);
		UINT GetFreeObjectCount() const;
		UINT GetMaxFreeObjectCount() const;

	private:
		UINT mMaxPoolSize;
		std::queue<T*> mQ;

	private:
	};


	

}