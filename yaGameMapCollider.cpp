#include "yaGameMapCollider.h"
#include "yaCollider.h"

namespace ya
{
	GameMapCollider::GameMapCollider(Vector2 colliderSize, Vector2 colliderOffset)
		: mpCollider(new Collider(colliderSize))
	{
		assert(mpCollider != nullptr);
		AddComponent(mpCollider);
		mpCollider->SetOffset(colliderOffset);
		mpCollider->SetColliderLayer(eColliderLayer::BACKGROUND);
	}
	void GameMapCollider::Initialize()
	{
		GameObject::Initialize();
	}
	void GameMapCollider::Tick()
	{
		GameObject::Tick();
	}
	void GameMapCollider::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}