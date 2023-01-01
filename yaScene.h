#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class GameObject;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);
		virtual void Enter();
		virtual void Exit();

		void AddGameObject(GameObject* object, eColliderLayer layer);
		void AddWeaponObject(GameObject* object);

		__forceinline const std::vector<GameObject*>& GetSpecifiedLayerGameObjects(eColliderLayer layer) const
		{
			return mObjects[static_cast<UINT>(layer)];
		}

		__forceinline std::vector<std::vector<GameObject*>>& GetGameObjects() { return mObjects; };
	
	protected:
		std::vector<std::vector<GameObject*>> mObjects;
	};
}

