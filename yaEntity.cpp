#include "yaEntity.h"

namespace ya
{
	Entity::Entity()
		: mName(L"")
		, mID(reinterpret_cast<UINT32>(this))
	{
	}
	Entity::~Entity()
	{
	}
}
