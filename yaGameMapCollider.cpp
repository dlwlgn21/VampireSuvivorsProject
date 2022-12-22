#include "yaGameMapCollider.h"
#include "yaCollider.h"
#include "yaPlayer.h"

namespace ya
{
	GameMapCollider::GameMapCollider(eMapColliderType type,Vector2 colliderSize, Vector2 colliderOffset)
		: mpCollider(new Collider(colliderSize))
		, meType(type)
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

	void GameMapCollider::OnCollisionEnter(Collider* other)
	{
		//switch (other->GetColliderLayer())
		//{
		//case eColliderLayer::PLAYER:
		//{
		//	Player* mpPlayer = static_cast<Player*>(other->GetOwner());
		//	assert(mpPlayer != nullptr);
		//	switch (meType)
		//	{
		//	case ya::eMapColliderType::TOP:
		//		mpPlayer->RestrictYPosition(-460.0f);
		//		break;
		//	case ya::eMapColliderType::BOT:
		//		break;
		//	case ya::eMapColliderType::TOP_DESK:
		//		break;
		//	case ya::eMapColliderType::BOT_DESK:
		//		break;
		//	case ya::eMapColliderType::PIANO_SIDE_BOOK:
		//		break;
		//	case ya::eMapColliderType::PIANO_MID_BOOK:
		//		break;
		//	case ya::eMapColliderType::PIANO:
		//		break;
		//	default:
		//		assert(false);
		//		break;
		//	}
		//	break;
		//}
		//default:
		//	break;
		//}
	}
	void GameMapCollider::OnCollisionStay(Collider* other)
	{
		switch (other->GetColliderLayer())
		{
		case eColliderLayer::PLAYER:
		{
			Player* pPlayer = static_cast<Player*>(other->GetOwner());
			assert(pPlayer != nullptr);
			Vector2 playerPos = pPlayer->GetPos();
			Vector2 pos = mpCollider->GetOffset();
			Vector2 size = mpCollider->GetSize();
			switch (meType)
			{
			case ya::eMapColliderType::TOP:
				pPlayer->RestrictYTopPosition(-460.0f);
				break;
			case ya::eMapColliderType::BOT:
				pPlayer->RestrictYBotPosition(455.0f);
				break;
			case ya::eMapColliderType::TOP_DESK:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			case ya::eMapColliderType::BOT_DESK:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			case ya::eMapColliderType::PIANO_SIDE_BOOK:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			case ya::eMapColliderType::PIANO_MID_BOOK:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			case ya::eMapColliderType::PIANO:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			default:
				assert(false);
				break;
			}
			break;
		}
		default:
			break;
		}
	}
	void GameMapCollider::OnCollisionExit(Collider* other)
	{
	}
	void GameMapCollider::OnEnterPlayer(Player* pPlayer, Vector2 colliderPos, Vector2 colliderSize)
	{
		Vector2 playerPos = pPlayer->GetPos();

		float leftXCoordinate = colliderPos.x - (colliderSize.x / 2);
		float rightXCoordinate = colliderPos.x + (colliderSize.x / 2);
		float topYCoordinate = colliderPos.y - (colliderSize.y / 2);
		float botYCoordinate = colliderPos.y + (colliderSize.y / 2);

		if (playerPos.x >= leftXCoordinate && playerPos.x <= rightXCoordinate &&
			playerPos.y >= topYCoordinate && playerPos.y <= botYCoordinate)
		{
			pPlayer->CanNotEnterPlayer(leftXCoordinate, rightXCoordinate, topYCoordinate, botYCoordinate);
		}
	}
}