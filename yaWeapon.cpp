#include "yaWeapon.h"
#include "yaCollider.h"

namespace ya
{
	Weapon::Weapon(eWeaponPenetratingType weaponPenetratingType, Vector2 spwanPos, int damage, float speed, float knockBackValue, float weaponDuration)
		: GameObject(spwanPos)
		, meWeaponPenetratingType(weaponPenetratingType)
		, mpCollider(new Collider())
		, mSpawnPosition(spwanPos)
		, mDamage(damage)
		, mSpeed(speed)
		, mKnockBackValue(knockBackValue)
		, mWeaponDuration(weaponDuration)
		, mDurationTimer(0)
		, mFunc({})
		, mSize({ 0.0f, 0.0f})
	{
		assert(mpCollider != nullptr);
		AddComponent(mpCollider);
		mpCollider->SetColliderLayer(eColliderLayer::PLAYER_PROJECTTILE);
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