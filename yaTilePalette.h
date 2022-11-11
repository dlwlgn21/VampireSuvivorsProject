#pragma once
#include "Common.h"

namespace ya
{
	class Image;
	class Tile;
	class TilePalette
	{
	public:
		TilePalette();
		~TilePalette();
		
		void Tick();
		void Render(HDC hdc);
		
		void CreateTile(UINT idx, Vector2 idxPos);
		//void CreateTiles();
		//
		//void Save();
		//void Load();
		__forceinline Image* GetAtlasImage() { return mAtlas; }
	private:
		Image* mAtlas;
		std::unordered_map<UINT64, Tile*> mTiles;
	};

}

