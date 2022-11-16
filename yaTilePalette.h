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

		void Save();
		void Load();
		void Load(const std::wstring& path);
		//void CreateTiles();

		__forceinline Image* GetAtlasImage() { return mAtlas; }
	private:
		Image* mAtlas;
		std::unordered_map<UINT64, Tile*> mTiles;
	};

}

