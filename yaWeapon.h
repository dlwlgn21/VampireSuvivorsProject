#pragma once
#include <random>
#include "yaGameObejct.h"

namespace ya
{
	enum class eWeaponPenetratingType
	{
		COMPLETE_PENETRATING,
		PARTIAL_PENETRATING,
		NO_PENETRATING,
		COUNT
	};

	class Collider;
	class Weapon : public GameObject
	{
	public:
		Weapon(eWeaponPenetratingType weaponPenetratingType, Vector2 spwanPos, int damage, float speed, float knockBackValue, float shootInterval);
		virtual ~Weapon() = default;

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		__forceinline eWeaponPenetratingType GetWeaponPenetratingType() const { return meWeaponPenetratingType; }
		__forceinline void SetWeaponPenetratingType(const eWeaponPenetratingType type) { meWeaponPenetratingType = type; }
		__forceinline void SetSize(const Vector2 size) { mSize = size; }
		__forceinline Vector2 GetSize() const { return mSize; }
		__forceinline int GetDamage() const { return mDamage; }
		__forceinline void SetDamage(const int damage) { mDamage = damage; }
		__forceinline void SetSpeed(const float speed) { mSpeed = speed; }
		__forceinline void SetShootInterval(const float newInterval) { mShootInterval = newInterval; }
		__forceinline void SetSpawnPos(const Vector2 newPos) { mSpawnPosition = newPos; }
		__forceinline void IncreaseDamage(const int amount) { mDamage += amount; }
		__forceinline void IncreaseSpeed(const float persentage) { assert(persentage >= 0.1f); mSpeed *= persentage; }

	protected:
		Collider* mpCollider;
		eWeaponPenetratingType meWeaponPenetratingType;
		
		Vector2 mSpawnPosition;
		Vector2 mSize;
		int mDamage;
		float mSpeed;
		float mKnockBackValue;
		float mShootInterval;
		float mShootTimer;
		BLENDFUNCTION mFunc;

	};

}

