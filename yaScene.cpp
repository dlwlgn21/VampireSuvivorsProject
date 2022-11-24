#include <cassert>
#include "yaGameObejct.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaCollisionManager.h"

namespace ya
{
	Scene::Scene()
	{
		SceneManager::SetCurrScene(this);
		mObjects.reserve(MAX_COLLIDER_LAYER);
		mObjects.resize(MAX_COLLIDER_LAYER);
		for (int i = 0; i < MAX_COLLIDER_LAYER; ++i)
		{
			mObjects[i].reserve(128);
		}
	}
	Scene::~Scene()
	{
		for (int i = 0; i < MAX_COLLIDER_LAYER; ++i)
		{
			for (int j = 0; j < mObjects[i].size(); ++j)
			{
				if (mObjects[i][j] == nullptr) { continue; }
				delete mObjects[i][j];
				mObjects[i][j] = nullptr;
			}
		}
	}

	void Scene::Initialize()
	{
		for (int i = 0; i < MAX_COLLIDER_LAYER; ++i)
		{
			for (int j = 0; j < mObjects[i].size(); ++j)
			{
				if (mObjects[i][j] == nullptr) { continue; }
				if (mObjects[i][j]->IsAlive())
				{
					mObjects[i][j]->Initialize();
				}
			}
		}
	}

	void Scene::Tick()
	{
		for (int i = 0; i < MAX_COLLIDER_LAYER; ++i)
		{
			for (int j = 0; j < mObjects[i].size(); ++j)
			{
				if (mObjects[i][j] == nullptr) { continue; }
				if (mObjects[i][j]->IsAlive())
				{
					mObjects[i][j]->Tick();
				}
			}
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (int i = 0; i < MAX_COLLIDER_LAYER; ++i)
		{
			for (int j = 0; j < mObjects[i].size(); ++j)
			{
				if (mObjects[i][j] == nullptr) { continue; }
				if (mObjects[i][j]->IsAlive())
				{
					mObjects[i][j]->Render(hdc);
				}
			}
		}
	}
	void Scene::Enter()
	{
	}
	void Scene::Exit()
	{
		CollisionManager::Clear();
	}
	void Scene::AddGameObject(GameObject* object, eColliderLayer layer)
	{
		assert(object != nullptr);
		mObjects[static_cast<UINT>(layer)].push_back(object);
	}

}