#pragma once
#include "yaGameObejct.h"

namespace ya
{
	enum class eMapColliderType
	{
		TOP,
		BOT,
		TOP_DESK,
		BOT_DESK,
		PIANO_SIDE_BOOK,
		PIANO_MID_BOOK,
		PIANO,
		LEFT_SCROLL_CHECKER,
		RIGHT_SCROLL_CHECKER,
		COUNT
	};
	class Player;
	class Collider;
	class GameMapCollider final : public GameObject
	{
	public:
		GameMapCollider(eMapColliderType type, Vector2 colliderSize, Vector2 pos);
		GameMapCollider(const GameMapCollider& other) = delete;
		GameMapCollider& operator=(const GameMapCollider& other) = delete;
		virtual ~GameMapCollider() = default;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		__forceinline eMapColliderType GetMapColliderType() { return meType; }

	private:
		void OnEnterPlayer(Player* pPlayer, Vector2 colliderPos, Vector2 colliderSize);
	private:
		eMapColliderType meType;
		Collider* mpCollider;
	};
}

