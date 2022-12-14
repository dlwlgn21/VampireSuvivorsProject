#pragma once
#include "yaScene.h"

namespace ya
{
	class Player;
	class ExpGem;
	class ExpGemObjPool;
	class MudMan;
	class Monster;
	class Sound;
	template<typename T> class MonsterObjPool;
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


		enum { BUFFER_LENGTH = 32 };
	private:
		void setColliderLayer();
	private:
		eSceneType mSceneType;
		Player* mpPlayer;
		bool mbUiFlag;
		HWND mHwnd;
		LOGFONT mFont;
		ExpGemObjPool* mpExpGemObjPool;
		MonsterObjPool<Monster>* mpMudManPool;
		MonsterObjPool<Monster>* mpGreenGhostPool;
		MonsterObjPool<Monster>* mpMedusaHeadPool;
		Sound* mpBGMSound;
	};
}

