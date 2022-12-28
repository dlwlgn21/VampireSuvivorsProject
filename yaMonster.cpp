#include "yaMonster.h"
#include "yaPlayer.h"
#include "yaCollider.h"

namespace ya
{
	Monster::Monster(Vector2 pos, Player* pPlayer, int hp, int damage, int exp, float speed)
		: GameObject(pos)
		, mpPlayer(pPlayer)
		, mHP(hp)
		, mDamage(damage)
		, mExp(exp)
		, mSpeed(speed)
		, mVelocityX(0.0f)
		, mVelocityY(0.0f)
		, mPlayerPos(mpPlayer->GetPos())
	{
		assert(mpPlayer != nullptr);
		assert(mHP != 0);
		assert(mDamage != 0);
		assert(mExp != 0);
		assert(std::abs(mSpeed) > FLT_EPSILON);
		//mPlayerPos = mpPlayer->GetPos();
	}

	void Monster::Tick()
	{
		mPlayerPos = mpPlayer->GetPos();
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