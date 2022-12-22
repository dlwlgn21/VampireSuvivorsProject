#pragma once
#include <cassert>
#include "yaScene.h"
#include "yaGameObejct.h"
#include "yaSceneManager.h"
#include "yaPlayer.h"

namespace ya
{
	namespace object
	{
		template<typename T>
		static __forceinline T* Instantiate(eColliderLayer colliderLayer)
		{
			T* gameObject = new T();
			Scene* scene = SceneManager::GetCurrentScene();
			scene->AddGameObject(static_cast<GameObject*>(gameObject), colliderLayer);
			return gameObject;
		}

		template<typename T>
		static __forceinline T* Instantiate(eColliderLayer colliderLayer, Vector2 pos)
		{
			T* gameObject = new T(pos);
			Scene* scene = SceneManager::GetCurrentScene();
			scene->AddGameObject(static_cast<GameObject*>(gameObject), colliderLayer);
			return gameObject;
		}
		template<typename T>
		static __forceinline T* Instantiate(eColliderLayer colliderLayer, const std::wstring& key)
		{
			T* gameObeject = new T(key);
			Scene* scene = SceneManager::GetCurrentScene();
			scene->AddGameObject(static_cast<GameObject*>(gameObeject), colliderLayer);
			return gameObeject;
		}

		template<typename T>
		static __forceinline T* InstantiateAtAnotherScene(eColliderLayer colliderLayer, const std::wstring& key, eSceneType sceneType)
		{
			T* gameObeject = new T(key);
			Scene* scene = SceneManager::GetSpecifiedScene(sceneType);
			scene->AddGameObject(static_cast<GameObject*>(gameObeject), colliderLayer);
			return gameObeject;
		}

		template<typename T>
		static __forceinline T* InstantiateAtAnotherScene(eColliderLayer colliderLayer, const std::wstring& key, const std::wstring& path, eSceneType sceneType)
		{
			T* gameObeject = new T(key, path);
			Scene* scene = SceneManager::GetSpecifiedScene(sceneType);
			scene->AddGameObject(static_cast<GameObject*>(gameObeject), colliderLayer);
			return gameObeject;
		}

		template<typename T>
		static __forceinline T* InstantiateAtAnotherScene(eColliderLayer colliderLayer, const std::wstring& key, eSceneType sceneType, Vector2 pos)
		{
			T* gameObeject = new T(key);
			gameObeject->SetPos(pos);
			Scene* scene = SceneManager::GetSpecifiedScene(sceneType);
			scene->AddGameObject(static_cast<GameObject*>(gameObeject), colliderLayer);
			return gameObeject;
		}

		//template<typename T>
		//static __forceinline T* InstantiateAtAnotherScene(eColliderLayer colliderLayer, Vector2 pos, eSceneType sceneType)
		//{
		//	T* gameObeject = new T(pos);
		//	Scene* scene = SceneManager::GetSpecifiedScene(sceneType);
		//	scene->AddGameObject(static_cast<GameObject*>(gameObeject), colliderLayer);
		//	return gameObeject;
		//}

		template<typename T>
		static __forceinline T* InstantiateAtAnotherScene(eColliderLayer colliderLayer, Vector2 pos, Player* pPlayer, eSceneType sceneType)
		{
			T* gameObeject = new T(pos, pPlayer);
			Scene* scene = SceneManager::GetSpecifiedScene(sceneType);
			scene->AddGameObject(static_cast<GameObject*>(gameObeject), colliderLayer);
			return gameObeject;
		}


		template<typename T>
		static __forceinline void Destory(GameObject* gameObject)
		{
			gameObject->DisableObject();
		}

		template<typename T>
		static __forceinline void Destory(GameObject* gameObject, float deathTime)
		{
			gameObject->DisableObject();
		}

		static __forceinline void Release()
		{
			Scene* currScene = SceneManager::GetCurrentScene();
			std::vector<std::vector<GameObject*>> objects = currScene->GetGameObjects();

			for (int i = 0; i < MAX_COLLIDER_LAYER; ++i)
			{
				// std::vector<GameObject*>::iterator iter
				for (auto iter = objects[i].begin(); iter != objects[i].end();)
				{
					if (!(*iter)->IsAlive())
					{
						iter = objects[i].erase(iter);
						continue;
					}
					++iter;
				}
			}
		}
	}
}