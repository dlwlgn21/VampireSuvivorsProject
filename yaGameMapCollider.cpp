#include "yaGameMapCollider.h"
#include "yaCollider.h"
#include "yaPlayer.h"
#include "yaObject.h"
#include "yaBGGmaeImage.h"

namespace ya
{
	GameMapCollider::GameMapCollider(eMapColliderType type,Vector2 colliderSize, Vector2 pos)
		: GameObject(pos)
		, mpCollider(new Collider(colliderSize))
		, meType(type)
	{
		assert(mpCollider != nullptr);
		AddComponent(mpCollider);
		// mpCollider->SetOffset(colliderOffset);
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
		if (!mbIsActive)
		{
			return;
		}
		switch (other->GetColliderLayer())
		{
		case eColliderLayer::PLAYER:
		{
			switch (meType)
			{
			case eMapColliderType::LEFT_SCROLL_CHECKER:
			{
				BGGmaeImage::IncreaseLeftScrollCount();
				BGGmaeImage* pBgGameImage = ya::object::InstantiateAtAnotherScene<BGGmaeImage>(eColliderLayer::BACKGROUND, L"BGGmaeMap", L"Resources\\Image\\MapTwo.bmp", eSceneType::PLAY_SCENE);
				pBgGameImage->SetLeftScrollCheck(true);
				pBgGameImage->Initialize();
				SetActive(false);
				break;
			}
			case eMapColliderType::RIGHT_SCROLL_CHECKER:
			{
				BGGmaeImage::IncreaseRightScrollCount();
				BGGmaeImage* pBgGameImage = ya::object::InstantiateAtAnotherScene<BGGmaeImage>(eColliderLayer::BACKGROUND, L"BGGmaeMap", L"Resources\\Image\\MapTwo.bmp", eSceneType::PLAY_SCENE);
				pBgGameImage->SetRightScrollCheck(true);
				pBgGameImage->Initialize();
				SetActive(false);
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}
	void GameMapCollider::OnCollisionStay(Collider* other)
	{
		if (!mbIsActive)
		{
			return;
		}
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
			case eMapColliderType::TOP:
				pPlayer->RestrictYTopPosition(-460.0f);
				break;
			case eMapColliderType::BOT:
				pPlayer->RestrictYBotPosition(455.0f);
				break;
			case eMapColliderType::TOP_DESK:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			case eMapColliderType::BOT_DESK:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			case eMapColliderType::PIANO_SIDE_BOOK:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			case eMapColliderType::PIANO_MID_BOOK:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			case eMapColliderType::PIANO:
			{
				OnEnterPlayer(pPlayer, pos, size);
				break;
			}
			default:
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