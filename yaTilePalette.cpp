#include <cassert>
#include "yaTilePalette.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaTile.h"
#include "yaObject.h"
#include "yaToolScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"

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
		if (IS_KEY_DOWN(eKeyCode::L_BUTTON))
		{
			if (GetFocus())
			{
				Vector2 mousePos = Input::GetMousePos();
				int x = mousePos.x / (TILE_SIZE_X * TILE_SCALE);
				int y = mousePos.y / (TILE_SIZE_Y * TILE_SCALE);
				ya::ToolScene* pToolScene = static_cast<ya::ToolScene*>(ya::SceneManager::GetCurrentScene());
				assert(pToolScene != nullptr);

				CreateTile(pToolScene->GetTileIdx(), Vector2(x, y));
			}
		}
	}

	void TilePalette::Render(HDC hdc)
	{
	}

	void TilePalette::CreateTile(UINT idx, Vector2 idxPos)
	{
		UnionTileID key{};
		key.left = idxPos.x;
		key.right = idxPos.y;

		auto iter = mTiles.find(key.ID);
		if (iter != mTiles.end())
		{
			iter->second->SetIdx(idx);		
		}

		Vector2 objectPos = idxPos * (TILE_SIZE_X * TILE_SCALE);

		Tile* tile = ya::object::Instantiate<Tile>(eColliderLayer::TILE, objectPos);
		tile->Initialize(mAtlas, idx);
		mTiles.insert(std::make_pair(key.ID, tile));
	}
}
