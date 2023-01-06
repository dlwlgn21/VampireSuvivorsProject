#pragma once
class ResultScene
{
};

#include "yaScene.h"

namespace ya
{
	class ResultScene : public Scene
	{
	public:
		ResultScene();
		virtual ~ResultScene() = default;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		void Enter() override;
		void Exit() override;
		__forceinline eSceneType GetSceneTpye() { return mSceneType; }

		enum { BUFFER_LENGTH = 32 };
		enum { X_POS = 830 };
		enum { INIT_Y_POS = 260 };
		enum { Y_DISTANCE = 40 };

	private:
		eSceneType mSceneType;
		HWND mHwnd;
		LOGFONT mFont;
		float mShowTimer;
	};
}
