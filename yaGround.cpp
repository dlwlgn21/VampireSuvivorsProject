#include "yaGround.h"
#include "yaPlayer.h"
#include "yaCollider.h"
#include "yaRigidBody.h"


namespace ya
{
	Ground::Ground()
		: GameObject()
	{
		Collider* pCollider = AddComponent<Collider>();
		pCollider->SetSize(Vector2(600.0f, 100.0f));

	}
	Ground::~Ground()
	{
	}
	void Ground::Tick()
	{
		GameObject::Tick();
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Ground::OnCollisionEnter(Collider* other)
	{
		GameObject* pPlayerObject = other->GetOwner();
		assert(pPlayerObject != nullptr);
		pPlayerObject->GetComponentOrNull<RigidBody>(eComponentType::RIGID_BODY)->SetIsGround(true);

		float fLen = fabs(other->GetPos().y - GetComponentOrNull<Collider>(eComponentType::COLLIDER)->GetPos().y);
		float fScale = other->GetScale().y / 2.0f + GetComponentOrNull<Collider>(eComponentType::COLLIDER)->GetScale().y / 2.0f;
		
		// Ground 위로 밀어주는 작업.
		if (fLen < fScale)
		{
			Vector2 playerPos = pPlayerObject->GetPos();
			playerPos.y -= (fScale - fLen) - 1.0f;
			pPlayerObject->SetPos(playerPos);
		}


	}
	void Ground::OnCollisionStay(Collider* other)
	{
	}
	void Ground::OnCollisionExit(Collider* other)
	{
	}
}