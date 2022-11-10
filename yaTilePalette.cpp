#include <cassert>
#include "yaTilePalette.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	TilePalette::TilePalette()
		: mAtlas(nullptr)
	{
		mAtlas = Resources::Load<Image>(L"TileAtlas", L"Resources\\Image\\Tile.bmp");
		assert(mAtlas != nullptr);
	}

	TilePalette::~TilePalette()
	{
	}

	void TilePalette::Tick()
	{
	}
	void TilePalette::Render(HDC hdc)
	{
	}
}
