#pragma once
#include "Common.h"
#include "def.h"
namespace ya
{
	class Collider;
	class Scene;
	class CollisionManager
	{
	public:
		static void Tick();
		static void SetLayer(eColliderLayer lLayer, eColliderLayer rLayer, bool value);
		static void CheckLayerCollision(Scene* scene, eColliderLayer lLayer, eColliderLayer rLayer);
		static void CheckColliderCollision(Collider* lCollider, Collider* rCollider);

		static bool CheckIntersect(Collider* lCollider, Collider* rCollider);


	private:
		static WORD mMatrix[MAX_COLLIDER_LAYER];
		static std::unordered_map<UINT64, bool> mCollisionInfo;
		static std::bitset<MAX_COLLIDER_LAYER> mBitMatrix;
	};
}

