#include "yaTile.h"
#include "yaImage.h"
#include "yaCamera.h"

namespace ya
{
	Tile::Tile(Vector2 pos)
		: GameObject(pos)
		, mAtlas(nullptr)
		, mY(-1)
		, mX(-1)
	{
	}
	//Tile::Tile(Image* atlas, int idx)
	//{
	//}

	Tile::~Tile()
	{
	}
	void Tile::Initialize(Image* atlas, int idx)
	{
		mIdx = idx;
		if (atlas == nullptr || idx < 0) { assert(false); }
		mAtlas = atlas;

		int maxCol = mAtlas->GetWidth() / TILE_SIZE_X;

		mY = idx / maxCol;
		mX = idx % maxCol;
	}

	void Tile::Tick()
	{
	}
	void Tile::Render(HDC hdc)
	{
		if (mAtlas == nullptr)	{return;}
		Vector2 renderPos = Camera::ToCameraPos(mPos);
		
		int tilePosX = mX * TILE_SIZE_X;
		int tilePosY = mY * TILE_SIZE_Y;

		TransparentBlt(
			hdc,
			static_cast<int>(renderPos.x),
			static_cast<int>(renderPos.y),
			static_cast<int>(TILE_SIZE_X * TILE_SCALE),
			static_cast<int>(TILE_SIZE_Y * TILE_SCALE),

			mAtlas->GetDC(),
			tilePosY,
			tilePosY,
			static_cast<int>(TILE_SIZE_X),
			static_cast<int>(TILE_SIZE_Y),
			RGB(255, 0, 255)
		);

	}
	void Tile::SetIdx(UINT idx)
	{
		mIdx = idx;

		int maxCol = mAtlas->GetWidth() / TILE_SIZE_X;

		mY = idx / maxCol;
		mX = idx % maxCol;
	}
}