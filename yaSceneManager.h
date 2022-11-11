#pragma once
#include "Common.h"

namespace ya
{
	class Scene;
	class SceneManager
	{
	public:
		static void Initialze();
		static void Tick();
		static void Render(HDC hdc);
		static void Release();
		static void ChangeSecne(eSceneType scene);
		static void DestroyGameobject();
		__forceinline static Scene* GetCurrentScene() { return mCurrentScenes; }
		__forceinline static Scene* GetSpecifiedScene(eSceneType sceneType) { return mScenes[static_cast<UINT>(sceneType)]; }
		__forceinline static void SetCurrScene(Scene* scene) { mCurrentScenes = scene; };

	private:
		static Scene* mScenes[static_cast<UINT>(eSceneType::COUNT)];
		static Scene* mCurrentScenes;
		static eSceneType mSceneType;
	};
}


