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
					// �浹�� �Ǿ����� �ȵǾ������� �˻������ �Ѵ�.
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
			{ mMatrix[row] |= (1 << col); }
		else 
			{ mMatrix[row] &= ~(1 << col); }

		/*if (value == true)	{ mBitMatrix[row] |= (0x1 << col); }
		else				{ mBitMatrix[row] &= ~(0x1 << col); }*/
	}

	void CollisionManager::CheckLayerCollision(Scene* scene, eColliderLayer lLayer, eColliderLayer rLayer)
	{
		// ��� left ������Ʈ��� right ������Ʈ���� ������ �����־�� ��.
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

				// �� �浹ü�� Layer��ȣ�� �ϴ� Ȯ���Ѵ�.
				CheckColliderCollision(chcheLeftCollider, cacheRightCollider);
			}
		}
	}

	void CollisionManager::CheckColliderCollision(Collider* lCollider, Collider* rCollider)
	{
		UnionColliderID id;														// Layer �ΰ��� �������� ����ü�� ��.
		id.left = lCollider->GetID();											// EntityConstructor->mID(reinterpret_cast<UINT32>(this)), �� �ּҰ�.
		id.right = rCollider->GetID();

		auto collistionInfoIter = mCollisionInfo.find(id.ID);					// �̹� �ε��� ������ Ȯ���ϱ� ���� ID �־ ã�ƺ�. ������ �ִٸ�(��, find ����� �ִٸ�) �ε����ִٴ� ��.
		if (collistionInfoIter == mCollisionInfo.end())							// ó�� �ε����ٸ� ����. ������ �������� �ϱ� ����
		{
			auto insertResult = mCollisionInfo.insert(std::make_pair(id.ID, false));
			if (insertResult.second == false)
				{ assert(false); }
			collistionInfoIter = insertResult.first;
		}

		if (CheckIntersect(lCollider, rCollider))
		{
			if (collistionInfoIter->second == false)							// ���� �� �� �浹
			{
				lCollider->OnCollisionEnter(rCollider);
				rCollider->OnCollisionEnter(lCollider);
				collistionInfoIter->second = true;
			}
			else																// �浹 ���ϋ� collistionInfoIter->second = true;
			{

				lCollider->OnCollisionStay(rCollider);
				rCollider->OnCollisionStay(lCollider);
			}
		}
		else
		{
			if (collistionInfoIter->second == true)								// �� ������
			{
				lCollider->OnCollisionExit(rCollider);
				rCollider->OnCollisionExit(lCollider);
				collistionInfoIter->second = false;
			}
			// �浹 X
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