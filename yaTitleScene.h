#pragma once
#include "yaScene.h"

namespace ya
{
	class TitleScene : public Scene
	{

	public:
		TitleScene();
		virtual ~TitleScene();

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

