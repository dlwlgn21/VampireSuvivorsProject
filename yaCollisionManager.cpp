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

	void CollisionManager::SetLayer(eColliderLayer lLayer, eColliderLayer rLayer, bool value)
	{
		// ������ �� �ʸ� ���� ���ؼ�. �� ������ ���� ���ؼ�
		// �� ���� ���ڸ� ������, �� ū ���ڸ� ����
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
			{ mMatrix[row] |= (0x1 << col); }
		else 
			{ mMatrix[row] &= ~(0x1 << col); }

		/*if (value == true)	{ mBitMatrix[row] |= (0x1 << col); }
		else				{ mBitMatrix[row] &= ~(0x1 << col); }*/
	}


	void CollisionManager::Tick()
	{
		Scene* currScene = SceneManager::GetCurrentScene();
		for (int i = 0; i < MAX_COLLIDER_LAYER; ++i)
		{
			for (int j = i; j < MAX_COLLIDER_LAYER; ++j)
			{
				if (mMatrix[i] & (0x1 << j))
				{
					// �浹�� �Ǿ����� �ȵǾ������� �˻������ �Ѵ�.
					checkLayerCollision(currScene,
						static_cast<eColliderLayer>(i),
						static_cast<eColliderLayer>(j)
					);
				}
			}
		}
	}

	void CollisionManager::checkLayerCollision(Scene* pScene, eColliderLayer leLayer, eColliderLayer reLayer)
	{
		// ��� left ������Ʈ��� right ������Ʈ���� ������ �����־�� ��.
		const std::vector<GameObject*>& lefts = pScene->GetSpecifiedLayerGameObjects(leLayer);
		const std::vector<GameObject*>& rights = pScene->GetSpecifiedLayerGameObjects(reLayer);
		Collider* pChcheLeftCollider;
		Collider* pCacheRightCollider;

		for (auto* pLeftObject : lefts)
		{
			pChcheLeftCollider = pLeftObject->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
			if (pChcheLeftCollider == nullptr) 
				{ continue; }
			for (auto* pRightObject : rights)
			{
				pCacheRightCollider = pRightObject->GetComponentOrNull<Collider>(eComponentType::COLLIDER);
				if (pCacheRightCollider == nullptr) 
					{ continue; }
				if (pLeftObject == pRightObject || pChcheLeftCollider == pCacheRightCollider) 
					{ continue; }
				checkColliderCollision(pChcheLeftCollider, pCacheRightCollider);
			}
		}
	}

	void CollisionManager::checkColliderCollision(Collider* lpCollider, Collider* rpCollider)
	{
		UnionColliderID id;														// Layer �ΰ��� �������� ����ü�� ��.
		id.left = lpCollider->GetID();											// EntityConstructor->mID(reinterpret_cast<UINT32>(this)), �� �ּҰ�.
		id.right = rpCollider->GetID();

		auto collistionInfoIter = mCollisionInfo.find(id.ID);					// �̹� �ε��� ������ Ȯ���ϱ� ���� ID �־ ã�ƺ�. ������ �ִٸ�(��, find ����� �ִٸ�) �ε����ִٴ� ��.
		
		if (collistionInfoIter == mCollisionInfo.end())							// ó�� �ε����ٸ� ����. ������ �������� �ϱ� ����
		{
			auto insertResult = mCollisionInfo.insert(std::make_pair(id.ID, false));
			if (insertResult.second == false)
				{ assert(false); }
			collistionInfoIter = insertResult.first;
		}

		if (checkIntersect(lpCollider, rpCollider))
		{
			if (collistionInfoIter->second == false)							// ���� �� �� �浹
			{
				lpCollider->OnCollisionEnter(rpCollider);
				rpCollider->OnCollisionEnter(lpCollider);
				collistionInfoIter->second = true;
			}
			else																// �浹 ���ϋ� collistionInfoIter->second = true;
			{
				lpCollider->OnCollisionStay(rpCollider);
				rpCollider->OnCollisionStay(lpCollider);
			}
		}
		else
		{
			if (collistionInfoIter->second == true)								// �� ������
			{
				lpCollider->OnCollisionExit(rpCollider);
				rpCollider->OnCollisionExit(lpCollider);
				collistionInfoIter->second = false;
			}
			// �浹 X
		}
	}

	bool CollisionManager::checkIntersect(Collider* lpCollider, Collider* rpCollider)
	{
		if (!lpCollider->GetOwner()->IsAlive())
			{ return false; }
		if (!rpCollider->GetOwner()->IsAlive())
			{ return false; }
		Vector2 leftPos = lpCollider->GetPos();
		Vector2 leftSize = lpCollider->GetSize();
		Vector2 rightPos = rpCollider->GetPos();
		Vector2 rightSize = rpCollider->GetSize();

		if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2 + rightSize.x / 2) &&
			fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2 + rightSize.y / 2))
			{ return true; }
		return false;
	}
	void CollisionManager::Clear()
	{
		memset(mMatrix, 0, sizeof(WORD) * MAX_COLLIDER_LAYER);
		mCollisionInfo.clear();
	}
}