#include "yaMonster.h"
#include "yaPlayer.h"
#include "yaCollider.h"

namespace ya
{
	Monster::Monster(Vector2 pos, Player* pPlayer, int hp, int damage, int exp)
		: GameObject(pos)
		, mpPlayer(pPlayer)
		, mHP(hp)
		, mDamage(damage)
		, mExp(exp)
	{
		assert(mpPlayer != nullptr);
		assert(mHP != 0);
		assert(mDamage != 0);
		assert(mExp != 0);
	}

	void Monster::OnCollisionEnter(Collider* other)
	{
		if (other != nullptr)
		{
			Player* pPlayer = static_cast<Player*>(other->GetOwner());
			if (mpPlayer == pPlayer)
			{
				mpPlayer->DamageFromMonster(mDamage);
			}
		}
	}
}