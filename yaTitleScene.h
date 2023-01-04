#pragma once
#include "yaScene.h"

namespace ya
{
	enum class eTitleSceneMenu
	{
		START,
		OPTION,
		EXIT,
		COUNT
	};
	class StartButton;
	class ButtonImageObject;
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
		__forceinline eSceneType GetSceneTpye() { return mSceneType; }
	private:
		eSceneType mSceneType;
	};
}

