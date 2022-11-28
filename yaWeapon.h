#pragma once
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

		inline void SetSize(Vector2 size) { mSize = size; }
		inline Vector2 GetSize() { return mSize; }

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

