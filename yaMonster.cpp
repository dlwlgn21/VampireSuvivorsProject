#include "yaMonster.h"
#include "yaPlayer.h"
#include "yaCollider.h"
#include "yaAI.h"

namespace ya
{
	Monster::Monster(Vector2 pos, Player* pPlayer, int hp, int damage, int exp, float speed)
		: GameObject(pos)
		, mpPlayer(pPlayer)
		, mpAI(new AI())
		, mHP(hp)
		, mDamage(damage)
		, mExp(exp)
		, mSpeed(speed)
		, mPlayerPos(mpPlayer->GetPos())
	{
		assert(mpPlayer != nullptr);
		assert(mHP != 0);
		assert(mDamage != 0);
		assert(mExp != 0);
		assert(std::abs(mSpeed) > FLT_EPSILON);
		assert(mpAI != nullptr);
		//mPlayerPos = mpPlayer->GetPos();
	}

	void Monster::Tick()
	{
		mPlayerPos = mpPlayer->GetPos();
		GameObject::Tick();
		mpAI->Tick();
	}

	Monster::~Monster()
	{
		if (mpAI !=  nullptr)
		{
			delete mpAI;
			mpAI = nullptr;
		}
	}

}