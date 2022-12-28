#pragma once
#include <random>
#include "yaGameObejct.h"
#include "yaMonster.h"

namespace ya
{

	class Collider;
	class Weapon : public GameObject
	{
	public:
		Weapon(Vector2 spwanPos, int damage, int penetratingCount,float speed, float knockBackValue, float weaponDuration);
		virtual ~Weapon() = default;

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		__forceinline void SetSize(const Vector2 size) { mSize = size; }
		__forceinline Vector2 GetSize() const { return mSize; }
		__forceinline int GetDamage() const { return mDamage; }
		__forceinline void SetDamage(const int damage) { mDamage = damage; }
		__forceinline void SetSpeed(const float speed) { mSpeed = speed; }
		__forceinline void SetShootInterval(const float newDuration) { mWeaponDuration = newDuration; }
		__forceinline void SetSpawnPos(const Vector2 newPos) { mSpawnPosition = newPos; }
		__forceinline void IncreaseDamage(const int amount) { mDamage += amount; }
		__forceinline void IncreaseSpeed(const float persentage) { assert(persentage >= 0.1f); mSpeed *= persentage; }

	protected:
		Collider* mpCollider;
		Vector2 mSpawnPosition;
		Vector2 mSize;
		int mDamage;
		int mPenetratingCount;
		int mPenetratingCounter;
		float mSpeed;
		float mKnockBackValue;
		float mWeaponDuration;
		float mDurationTimer;
		BLENDFUNCTION mFunc;

	};

}

