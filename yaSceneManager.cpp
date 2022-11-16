#include "yaSceneManager.h"
#include "yaLogoScene.h"
#include "yaPlayScene.h"
#include "yaTitleScene.h"
#include "yaEndingScene.h"
#include "yaObject.h"
#include "yaToolScene.h"
namespace ya
{

	Scene* SceneManager::mScenes[static_cast<UINT>(eSceneType::COUNT)] = {};
	Scene* SceneManager::mCurrentScenes = nullptr;

	void SceneManager::Initialze()
	{
		// 모든 씬들을 초기화
		mScenes[static_cast<UINT>(eSceneType::LOGO_SCENE)] = new LogoScene();
		mScenes[static_cast<UINT>(eSceneType::LOGO_SCENE)]->Initialize();

		mScenes[static_cast<UINT>(eSceneType::TITLE_SCENE)] = new TitleScene();
		mScenes[static_cast<UINT>(eSceneType::TITLE_SCENE)]->Initialize();

		mScenes[static_cast<UINT>(eSceneType::PLAY_SCENE)] = new PlayScene();
		mScenes[static_cast<UINT>(eSceneType::PLAY_SCENE)]->Initialize();

		mScenes[static_cast<UINT>(eSceneType::ENDING_SCENE)] = new EndingScene();
		mScenes[static_cast<UINT>(eSceneType::ENDING_SCENE)]->Initialize();

		ChangeSecne(eSceneType::LOGO_SCENE);
#if 0
		mScenes[static_cast<UINT>(eSceneType::TOOL_SCENE)] = new ToolScene();
		mScenes[static_cast<UINT>(eSceneType::TOOL_SCENE)]->Initialize();

		ChangeSecne(eSceneType::TOOL_SCENE);
#endif

	}

	void SceneManager::Tick()
	{
		// 현재 씬을 update Tick
		mCurrentScenes->Tick();
	}
	void SceneManager::Render(HDC hdc)
	{
		// 현재 씬 렌더링
		mCurrentScenes->Render(hdc);
	}
	void SceneManager::Release()
	{
		// 프로그램을 종료할 떄 한번만 호출
		for (auto* scene : mScenes)
		{
			if (scene == nullptr) { continue; }
			delete scene;
			scene = nullptr;
		}
	}
	void SceneManager::ChangeSecne(eSceneType scene)
	{
		if (mScenes[static_cast<UINT>(scene)] == nullptr) { assert(false); return; }
		mCurrentScenes->Exit();
		mCurrentScenes = mScenes[static_cast<UINT>(scene)];
		mCurrentScenes->Enter();
	}
	void SceneManager::DestroyGameobject()
	{
		ya::object::Release();
	}
}