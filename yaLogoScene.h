#pragma once
#include "yaScene.h"
#include "yaImage.h"
namespace ya
{
	class LogoScene : public Scene
	{

	public:
		LogoScene();
		virtual ~LogoScene();

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
