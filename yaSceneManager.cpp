#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTitleScene.h"
#include "yaResultScene.h"
#include "yaObject.h"
namespace ya
{

	Scene* SceneManager::mScenes[static_cast<UINT>(eSceneType::COUNT)] = {};
	Scene* SceneManager::mCurrentScenes = nullptr;

	void SceneManager::Initialze()
	{
		// ��� ������ �ʱ�ȭ
		mScenes[static_cast<UINT>(eSceneType::TITLE_SCENE)] = new TitleScene();
		mScenes[static_cast<UINT>(eSceneType::TITLE_SCENE)]->Initialize();

		mScenes[static_cast<UINT>(eSceneType::PLAY_SCENE)] = new PlayScene();
		mScenes[static_cast<UINT>(eSceneType::PLAY_SCENE)]->Initialize();

		mScenes[static_cast<UINT>(eSceneType::RESULT_SCENE)] = new ResultScene();
		mScenes[static_cast<UINT>(eSceneType::RESULT_SCENE)]->Initialize();
		ChangeSecne(eSceneType::TITLE_SCENE);
	}

	void SceneManager::Tick()
	{
		// ���� ���� update Tick
		mCurrentScenes->Tick();
	}
	void SceneManager::Render(HDC hdc)
	{
		// ���� �� ������
		mCurrentScenes->Render(hdc);
	}
	void SceneManager::Release()
	{
		// ���α׷��� ������ �� �ѹ��� ȣ��
		for (auto* scene : mScenes)
		{
			if (scene == nullptr) { continue; }
			delete scene;
			scene = nullptr;
		}
	}
	void SceneManager::ChangeSecne(eSceneType scene)
	{
		assert(mScenes[static_cast<UINT>(scene)] != nullptr);
		mCurrentScenes->Exit();
		mCurrentScenes = mScenes[static_cast<UINT>(scene)];
		mCurrentScenes->Enter();
	}
	void SceneManager::DestroyGameobject()
	{
		ya::object::Release();
	}
}