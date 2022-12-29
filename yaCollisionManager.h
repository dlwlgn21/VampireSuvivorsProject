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
		static void Clear();
	private:
		static void checkLayerCollision(Scene* scene, eColliderLayer lLayer, eColliderLayer rLayer);
		static void checkColliderCollision(Collider* lCollider, Collider* rCollider);
		static bool checkIntersect(Collider* lCollider, Collider* rCollider);

	private:
		static WORD mMatrix[MAX_COLLIDER_LAYER];
		static std::unordered_map<UINT64, bool> mCollisionInfo;
		static std::bitset<MAX_COLLIDER_LAYER> mBitMatrix;
	};
}

