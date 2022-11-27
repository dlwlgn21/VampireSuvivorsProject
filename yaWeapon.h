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

	class Weapon : public GameObject
	{
	public:
		Weapon(eWeaponType weaponType, Vector2 spwanPos, Vector2 size, int damage, int count, float speed, float mKnockBackValue);
		virtual ~Weapon() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		virtual void Shoot();
	private:
		eWeaponType meWeaponType;
		
		Vector2 mSpawnPosition;
		Vector2 mSize;
		int mDamage;
		int mCount;
		float mSpeed;
		float mKnockBackValue;

	};

}

