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

	private:
		eSceneType mSceneType;
		TilePalette* mpTilePalette;
	};
}

