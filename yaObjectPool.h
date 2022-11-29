#pragma once
#include "Common.h"

namespace ya
{
	template<typename T>
	class ObjectPool
	{
	public:
		ObjectPool(UINT maxPoolSize);
		ObjectPool(const ObjectPool& other) = delete;
		ObjectPool& operator=(const ObjectPool& other) = delete;
		
		~ObjectPool();

		T* Get();
		void Return(T* ptr);
		UINT GetFreeObjectCount() const;
		UINT GetMaxFreeObjectCount() const;

	private:
		UINT mMaxPoolSize;
		std::queue<T*> mQ;
	};


	template<typename T>
	ObjectPool<T>::ObjectPool(UINT maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{
	}

	template<typename T>
	ObjectPool<T>::~ObjectPool()
	{
		while (!mQ.empty())
		{
			delete mQ.front();
			mQ.pop();
		}
	}

	template<typename T>
	T* ObjectPool<T>::Get()
	{
		if (mQ.empty())
		{
			return new T();
		}
		T* ret = mQ.front();
		mQ.pop();
		return ret;
	}

	template<typename T>
	void ObjectPool<T>::Return(T* ptr)
	{
		if (mQ.size() >= mMaxPoolSize)
		{
			delete ptr;
			return;
		}
		mQ.push(ptr);
	}

	template<typename T>
	UINT ObjectPool<T>::GetFreeObjectCount() const
	{
		return mQ.size();
	}

	template<typename T>
	UINT ObjectPool<T>::GetMaxFreeObjectCount() const
	{
		return mMaxPoolSize;
	}

}

