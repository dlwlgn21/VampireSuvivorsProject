#pragma once
#include "yaScene.h"

namespace ya
{
	class EndingScene : public Scene
	{

	public:
		EndingScene();
		virtual ~EndingScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		void Enter() override;
		void Exit() override;
		inline eSceneType GetSceneTpye() { return mSceneType; }
	private:
		eSceneType mSceneType;
	};
}

