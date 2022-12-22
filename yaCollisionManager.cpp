#include "yaCollisionManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaGameObejct.h"
#include "yaCollider.h"

namespace ya
{
	WORD CollisionManager::mMatrix[MAX_COLLIDER_LAYER] = { 0, };
	std::bitset<MAX_COLLIDER_LAYER> CollisionManager::mBitMatrix;
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionInfo;

	void CollisionManager::Tick()
	{
		Scene* currScene = SceneManager::GetCurrentScene();
		for (int i = 0; i < MAX_COLLIDER_LAYER; ++i)
		{
			for (int j = 0; j < MAX_COLLIDER_LAYER; ++j)
			{
				if (mMatrix[i] & (0x1 << j))
				{
					// 충돌이 되었는지 안되었는지를 검사해줘야 한다.
					CheckLayerCollision(currScene,
						static_cast<eColliderLayer>(i),
						static_cast<eColliderLayer>(j)
					);
				}
			}
		}
	}
	void CollisionManager::SetLayer(eColliderLayer lLayer, eColliderLayer rLayer, bool value)
	{
		// 무조건 한 쪽만 쓰기 위해서. 즉 반절만 쓰기 위해서
		// 더 작은 숫자를 행으로, 더 큰 숫자를 열로
		UINT row = 0;
		UINT col = 0;

		UINT iLeft = static_cast<UINT>(lLayer);
		UINT iRight = static_cast<UINT>(rLayer);

		row = iLeft;
		col = iRight;

		if (iRight <= iLeft)
		{
			row = iRight;
			col = iLeft;
		}

		if (value == true) 
			{ mMatrix[row] |= (1 << col); }
		else 
			{ mMatrix[row] &= ~(1 << col); }

		/*if (value == true)	{ mBitMatrix[row] |= (0x1 << col); }
		else				{ mBitMatrix[row] &= ~(0x1 << col); }*/
	}

	void CollisionManager::CheckLayerCollision(Scene* scene, eColliderLayer lLayer, eColliderLayer rLayer)
	{
		// 모든 left 오브젝트들과 right 오브젝트들을 가져와 비교해주어야 함.
		std::vector<GameObject*>& lefts = scene->GetSpecifiedLayerGameObjects(lLayer);
		std::vector<GameObject*>& rights = scene->GetSpecifiedLayerGameObjects(rLayer);
		Collider* chcheLeftCollider;
		Collider* cacheRightCollider;

		for (auto* leftObject : lefts)
		{
			chcheLeftCollider = leftObject->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
			if (chcheLeftCollider == nullptr) 
				{ continue; }
			for (auto* rightObject : rights)
			{
				cacheRightCollider = rightObject->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
				if (cacheRightCollider == nullptr) 
					{ continue; }

				if (leftObject == rightObject || chcheLeftCollider == cacheRightCollider) { continue; }

				// 두 충돌체의 Layer번호를 일단 확인한다.
				CheckColliderCollision(chcheLeftCollider, cacheRightCollider);
			}
		}
	}

	void CollisionManager::CheckColliderCollision(Collider* lCollider, Collider* rCollider)
	{
		UnionColliderID id;														// Layer 두개로 묶기위해 공용체로 씀.
		id.left = lCollider->GetID();											// EntityConstructor->mID(reinterpret_cast<UINT32>(this)), 즉 주소값.
		id.right = rCollider->GetID();

		auto collistionInfoIter = mCollisionInfo.find(id.ID);					// 이미 부딪힌 놈인지 확인하기 위해 ID 넣어서 찾아봄. 정보가 있다면(즉, find 결과가 있다면) 부딪혀있다는 것.
		if (collistionInfoIter == mCollisionInfo.end())							// 처음 부딪혔다면 진입. 정보를 만들어줘야 하기 때문
		{
			auto insertResult = mCollisionInfo.insert(std::make_pair(id.ID, false));
			if (insertResult.second == false)
				{ assert(false); }
			collistionInfoIter = insertResult.first;
		}

		if (CheckIntersect(lCollider, rCollider))
		{
			if (collistionInfoIter->second == false)							// 최초 한 번 충돌
			{
				lCollider->OnCollisionEnter(rCollider);
				rCollider->OnCollisionEnter(lCollider);
				collistionInfoIter->second = true;
			}
			else																// 충돌 중일떄 collistionInfoIter->second = true;
			{

				lCollider->OnCollisionStay(rCollider);
				rCollider->OnCollisionStay(lCollider);
			}
		}
		else
		{
			if (collistionInfoIter->second == true)								// 막 나갈때
			{
				lCollider->OnCollisionExit(rCollider);
				rCollider->OnCollisionExit(lCollider);
				collistionInfoIter->second = false;
			}
			// 충돌 X
		}
	}

	bool CollisionManager::CheckIntersect(Collider* lCollider, Collider* rCollider)
	{
		if (!lCollider->GetOwner()->IsAlive())
			{ return false; }
		if (!rCollider->GetOwner()->IsAlive())
			{ return false; }
		Vector2 leftPos = lCollider->GetPos();
		Vector2 leftScale = lCollider->GetSize();
		Vector2 rightPos = rCollider->GetPos();
		Vector2 rightScale = rCollider->GetSize();

		if (fabs(leftPos.x - rightPos.x) < fabs(leftScale.x / 2 + rightScale.x / 2) &&
			fabs(leftPos.y - rightPos.y) < fabs(leftScale.y / 2 + rightScale.y / 2))
			{ return true; }
		return false;
	}
	void CollisionManager::Clear()
	{
		memset(mMatrix, 0, sizeof(WORD) * MAX_COLLIDER_LAYER);
		mCollisionInfo.clear();
	}
}