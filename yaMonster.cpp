#include "yaMonster.h"

namespace ya
{
	Monster::Monster(Vector2 pos, int hp)
		: GameObject(pos)
		, mHP(hp)
	{
	}

}