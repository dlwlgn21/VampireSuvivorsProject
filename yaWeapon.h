#pragma once
#include <random>
#include "yaGameObejct.h"
namespace ya
{
	enum class eWeaponType
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
		Weapon(eWeaponType weaponType, Vector2 spwanPos, int damage, int count, float speed, float knockBackValue, float shootInterval);
		virtual ~Weapon() = default;

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		__forceinline eWeaponType GetWeaponType() { return meWeaponType; }
		__forceinline void SetSize(Vector2 size) { mSize = size; }
		__forceinline Vector2 GetSize() { return mSize; }
		__forceinline int GetDamage() { return mDamage; }
		__forceinline void SetDamage(int newDamage) { mDamage = newDamage; }
		__forceinline void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
		__forceinline void SetShootInterval(float newInterval) { mShootInterval = newInterval; }
		__forceinline void SetSpawnPos(Vector2 newPos) { mSpawnPosition = newPos; }
	protected:
		Collider* mpCollider;
		eWeaponType meWeaponType;
		
		Vector2 mSpawnPosition;
		Vector2 mSize;
		int mDamage;
		int mCount;
		float mSpeed;
		float mKnockBackValue;
		float mShootInterval;
		float mShootTimer;
		BLENDFUNCTION mFunc;

	};

}

