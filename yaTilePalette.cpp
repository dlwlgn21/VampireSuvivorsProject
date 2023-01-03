#include <cassert>
#include "framework.h"
#include "VampireSuvivorsProject.h"
#include <commdlg.h>
#include "yaTilePalette.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaTile.h"
#include "yaObject.h"
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
				int x = static_cast<int>(mousePos.x / (TILE_SIZE_X * TILE_SCALE));
				int y = static_cast<int>(mousePos.y / (TILE_SIZE_Y * TILE_SCALE));
				ya::ToolScene* pToolScene = static_cast<ya::ToolScene*>(ya::SceneManager::GetCurrentScene());
				assert(pToolScene != nullptr);

				CreateTile(pToolScene->GetTileIdx(), Vector2(static_cast<float>(x), static_cast<float>(y)));
			}
		}
	}

	void TilePalette::Render(HDC hdc)
	{
	}

	void TilePalette::CreateTile(UINT idx, Vector2 idxPos)
	{
		UnionTileID key{};
		key.left = static_cast<UINT32>(idxPos.x);
		key.right = static_cast<UINT32>(idxPos.y);

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
	void TilePalette::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn)) { assert(false); return; }

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"wb");
		if (pFile == nullptr)				{ assert(false); return; }

		auto iter = mTiles.begin();
		for (; iter != mTiles.end(); ++iter)
		{
			int tileIndex = (*iter).second->GetIdx();
			fwrite(&tileIndex, sizeof(int), 1, pFile);

			UnionTileID id;
			id.ID = (*iter).first;
			fwrite(&id.ID, sizeof(UINT64), 1, pFile);
		}

		fclose(pFile);
	}
	void TilePalette::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&ofn)) { assert(false); return; }

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");
		if (pFile == nullptr)				{ assert(false); return; }

		while (true)
		{
			int tileIdx = 0;
			UnionTileID id;
			if (fread(&tileIdx, sizeof(int), 1, pFile) == NULL)		{ break; }
			if (fread(&id.ID, sizeof(UINT64), 1, pFile) == NULL)	{ break; }
			CreateTile(tileIdx, Vector2(static_cast<float>(id.left), static_cast<float>(id.right)));
		}
		fclose(pFile);
	}

	void TilePalette::Load(const std::wstring& path)
	{
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, path.c_str(), L"rb");
		if (pFile == nullptr) { assert(false); return; }

		while (true)
		{
			int tileIdx = 0;
			UnionTileID id;
			if (fread(&tileIdx, sizeof(int), 1, pFile) == NULL) { break; }
			if (fread(&id.ID, sizeof(UINT64), 1, pFile) == NULL) { break; }
			CreateTile(tileIdx, Vector2(static_cast<float>(id.left), static_cast<float>(id.right)));
		}
		fclose(pFile);
	}
}
