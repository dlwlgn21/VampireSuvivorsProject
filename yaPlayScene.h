#pragma once
#include "yaScene.h"
namespace ya
{
	class Player;
	class PlayScene : public Scene
	{

	public:
		PlayScene();
		virtual ~PlayScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		void Enter() override;
		void Exit() override;
		inline eSceneType GetSceneTpye() { return mSceneType; }

	private:
		eSceneType mSceneType;
		Player* mpPlayer;
		bool mbUiFlag;
		HWND mHwnd;
		LOGFONT mFont;
	};
}

