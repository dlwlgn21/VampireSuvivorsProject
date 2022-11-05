#include "yaComponent.h"
#include "yaGameObejct.h"

namespace ya
{
	Component::Component(eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}

	Component::~Component()
	{
	}

	void Component::Tick()
	{
	}

	void Component::Render(HDC hdc)
	{
	}
}