#pragma once
#include "yaGameObejct.h"
namespace ya
{
	class Image;
	class Tile : public GameObject
	{
	public:
		Tile(Vector2 pos);
		//Tile(Image* atlas, int idx);
		~Tile();

		void Initialize(Image* atlas, int idx);
		void Tick() override;
		void Render(HDC hdc) override;

		void SetIdx(UINT idx);
		inline UINT GetIdx() { return mIdx; }

	private:
		Image* mAtlas;
		UINT mIdx;
		UINT mX;
		UINT mY;
	};

}

