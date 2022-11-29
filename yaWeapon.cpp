#include "yaWeapon.h"
#include "yaCollider.h"

namespace ya
{
	Weapon::Weapon(eWeaponType weaponType, Vector2 spwanPos, int damage, float speed, float knockBackValue, float shootInterval)
		: GameObject(spwanPos)
		, meWeaponType(weaponType)
		, mpCollider(new Collider())
		, mSpawnPosition(spwanPos)
		, mDamage(damage)
		, mSpeed(speed)
		, mKnockBackValue(knockBackValue)
		, mShootInterval(shootInterval)
		, mShootTimer(0)
		, mFunc({})
	{
		assert(mpCollider != nullptr);
		AddComponent(mpCollider);
		mFunc.BlendOp = AC_SRC_OVER;
		mFunc.BlendFlags = 0;
		mFunc.AlphaFormat = AC_SRC_ALPHA;
		mFunc.SourceConstantAlpha = 255;
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
}