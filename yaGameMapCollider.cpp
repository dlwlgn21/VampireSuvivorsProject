#include "yaGameMapCollider.h"
#include "yaCollider.h"
#include "yaPlayer.h"
#include "yaObject.h"
#include "yaBGGmaeImage.h"
#include "yaTime.h"

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
		mpCollider->SetIsWorking(true);
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
				mpCollider->SetIsWorking(false);
				break;
			}
			case eMapColliderType::RIGHT_SCROLL_CHECKER:
			{
				BGGmaeImage::IncreaseRightScrollCount();
				BGGmaeImage* pBgGameImage = ya::object::InstantiateAtAnotherScene<BGGmaeImage>(eColliderLayer::BACKGROUND, L"BGGmaeMap", L"Resources\\Image\\MapTwo.bmp", eSceneType::PLAY_SCENE);
				pBgGameImage->SetRightScrollCheck(true);
				pBgGameImage->Initialize();
				SetActive(false);
				mpCollider->SetIsWorking(false);

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
			GameObject* pOtherObject = pPlayer;
			Vector2 objPos = pPlayer->GetPos();
			Vector2 pos = mpCollider->GetOffset();
			Vector2 otherColliderSize = mpCollider->GetSize();
			switch (meType)
			{
			case eMapColliderType::TOP:
			{
				pPlayer->RestrictYTopPosition(-460.0f);
				break;
			}
			case eMapColliderType::BOT:
			{
				pPlayer->RestrictYBotPosition(455.0f);
				break;
			}
			default:
				break;
			}
			//case eMapColliderType::TOP_DESK:
			//{
			//	OnEnterPlayer(pPlayer, pos, size);
			//	break;
			//}
			//case eMapColliderType::BOT_DESK:
			//{
			//	OnEnterPlayer(pPlayer, pos, size);
			//	break;
			//}
			//case eMapColliderType::PIANO_SIDE_BOOK:
			//{
			//	OnEnterPlayer(pPlayer, pos, size);
			//	break;
			//}
			//case eMapColliderType::PIANO_MID_BOOK:
			//{
			//	OnEnterPlayer(pPlayer, pos, size);
			//	break;
			//}
			//case eMapColliderType::PIANO:
			//{
			//	OnEnterPlayer(pPlayer, pos, size);
			//	break;
			//}
			
			//case eMapColliderType::TOP_DESK:
			//case eMapColliderType::BOT_DESK:
			//case eMapColliderType::PIANO_SIDE_BOOK:
			//case eMapColliderType::PIANO_MID_BOOK:
			//case eMapColliderType::PIANO:
			//{
			//	Vector2 myCollderSize = mpCollider->GetSize();
			//	GameObject* pFixedObject;
			//	GameObject* pMovingObject;
			//	float myLeft = mPos.x - myCollderSize.x / 2;
			//	float myRight = mPos.x + myCollderSize.x / 2;

			//	float otherLeft = objPos.x - otherColliderSize.x / 2;
			//	float otherRight = objPos.x + otherColliderSize.x / 2;

			//	float pushXLength = 0.0f;

			//	if (myLeft <= otherLeft)
			//	{
			//		pFixedObject = this;
			//		pMovingObject = pOtherObject;
			//		pushXLength = std::abs(myRight - otherLeft);
			//	}
			//	else
			//	{
			//		pFixedObject = pOtherObject;
			//		pMovingObject = this;
			//		pushXLength = std::abs(otherRight - myLeft);
			//	}
			//	if (std::abs(pushXLength) > FLT_EPSILON)
			//	{
			//		pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x + (pushXLength * Time::DeltaTime()), pMovingObject->GetPos().y));
			//	}


			//	float myTop = mPos.y - myCollderSize.y / 2;
			//	float myBot = mPos.y + myCollderSize.y / 2;

			//	float otherTop = objPos.y - otherColliderSize.y / 2;
			//	float otherBot = objPos.y + otherColliderSize.y / 2;

			//	float pushYlengh = 0.0f;
			//	// my의 y좌표가 other의 y좌표보다 위에 있으면
			//	if (myTop <= otherTop)
			//	{
			//		pFixedObject = this;
			//		pMovingObject = pOtherObject;
			//		//pushYlengh = -(otherLeftTopY - myRightBottomY);
			//		pushYlengh = std::abs(otherTop - myBot);
			//	}
			//	// my의 오른쪽 y좌표가 other의 오른족 y좌표보다 아래에 있으면
			//	else
			//	{
			//		pFixedObject = pOtherObject;
			//		pMovingObject = this;
			//		pushYlengh = std::abs(otherBot - myTop);
			//	}

			//	if (std::abs(pushYlengh) > FLT_EPSILON)
			//	{
			//		pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x, pMovingObject->GetPos().y + (pushYlengh * Time::DeltaTime())));
			//	}

			//	break;
			//}
			//default:
			//	break;
			//}
			//break;
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