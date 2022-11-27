#include "yaWeapon.h"


namespace ya
{
	Weapon::Weapon(eWeaponType weaponType, Vector2 spwanPos, Vector2 size, int damage, int count, float speed, float knockBackValue)
		: GameObject(spwanPos)
		, meWeaponType(weaponType)
		, mSpawnPosition(spwanPos)
		, mSize(size)
		, mDamage(damage)
		, mCount(count)
		, mSpeed(speed)
		, mKnockBackValue(knockBackValue)
	{
	}

	void Weapon::Tick()
	{
		GameObject::Tick();
	}

	void Weapon::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Weapon::OnCollisionEnter(Collider* other)
	{
	}
	void Weapon::OnCollisionStay(Collider* other)
	{
	}
	void Weapon::OnCollisionExit(Collider* other)
	{
	}
	void Weapon::Shoot()
	{
	}
}