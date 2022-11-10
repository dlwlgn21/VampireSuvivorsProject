#pragma once
#include "yaTile.h"

namespace ya
{
	class Image;
	class TilePalette
	{
	public:
		TilePalette();
		~TilePalette();
		
		void Tick();
		void Render(HDC hdc);
		
		//void CreateTile();
		//void CreateTiles();
		//
		//void Save();
		//void Load();
		__forceinline Image* GetAtlasImage() { return mAtlas; }
	private:
		Image* mAtlas;

	};

}

