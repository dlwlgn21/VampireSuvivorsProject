#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Collider;
	class GameMapCollider final : public GameObject
	{
	public:
		GameMapCollider(Vector2 colliderSize, Vector2 colliderOffset);
		GameMapCollider(const GameMapCollider& other) = delete;
		GameMapCollider& operator=(const GameMapCollider& other) = delete;
		virtual ~GameMapCollider() = default;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	private:
		Collider* mpCollider;
	};
}

