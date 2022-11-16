#pragma once
#include "yaScene.h"
#include "yaTilePalette.h"
namespace ya
{
	class Image;
	class ToolScene : public Scene
	{

	public:
		ToolScene();
		virtual ~ToolScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		void Enter() override;
		void Exit() override;
		inline eSceneType GetSceneTpye() { return mSceneType; }
		inline Image* GetAtlasImage(){ return mpTilePalette->GetAtlasImage(); }
		void SetTileIdx(int idx) { mTileIdx = idx; }
		UINT GetTileIdx() { return mTileIdx; }
		void SaveTilePallete();
		void LoadTilePallete();
		void LoadTilePallete(const std::wstring& path);

	private:
		eSceneType mSceneType;
		TilePalette* mpTilePalette;
		UINT mTileIdx;
	};
}

