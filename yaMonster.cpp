#include "yaMonster.h"
#include "yaPlayer.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaWeapon.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaExpGem.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaExpGemObjPool.h"
#include "yaMonsterObjPool.h"


namespace ya
{
	Monster::Monster(
		const MonsterCreateInfo& monInfo,
		const std::wstring& imageRightMoveKey,
		const std::wstring& imageLeftMoveKey,
		const std::wstring& imageRightDeathKey,
		const std::wstring& imageLeftDeathKey,

		const std::wstring& imageRightMovePath,
		const std::wstring& imageLeftMovePath,
		const std::wstring& imageRightDeathPath,
		const std::wstring& imageLeftDeathPath,
		ExpGemObjPool* pExpGemObjPool,
		MonsterObjPool<Monster>* pMonsterObjPool
	)
		: GameObject(monInfo.Pos)
		, mpPlayer(monInfo.PtrPlayer)
		, mHP(monInfo.Hp)
		, mDamage(monInfo.Damage)
		, mExp(monInfo.Exp)
		, mSpeed(monInfo.Speed)
		, mPlayerPos(mpPlayer->GetPos())
		, meLookDir(eMonsterLookDir::COUNT)
		, mImageRightMoveKey(imageRightMoveKey)
		, mImageLeftMoveKey(imageLeftMoveKey)
		, mImageRightDeathKey(imageRightDeathKey)
		, mImageLeftDeathKey(imageLeftDeathKey)
		, mpRightImage(Resources::Load<Image>(imageRightMoveKey, imageRightMovePath))
		, mpLeftImage(Resources::Load<Image>(imageLeftMoveKey, imageLeftMovePath))
		, mpRightDeathImage(Resources::Load<Image>(imageRightDeathKey, imageRightDeathPath))
		, mpLeftDeathImage(Resources::Load<Image>(imageLeftDeathKey, imageLeftDeathPath))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(monInfo.AnimMoveSize))
		, mAnimMoveSize(monInfo.AnimMoveSize)
		, mAnimDeathSize(monInfo.AnimDeathSize)
		, mAnimOffset(monInfo.AnimOffset)
		, mAnimImageCount(monInfo.AnimImageCount)
		, mAnimDeathImageCount(monInfo.AnimDeathImageCount)
		, mAnimDuration(monInfo.AnimDuration)
		, mAnimDeathCounter(monInfo.AnimDeathDuration)
		, mbIsDeathFromWeapon(false)
		, mpExpGemObjPool(pExpGemObjPool)
		, mpMonsterObjPool(pMonsterObjPool)
	{
		assert(mpPlayer != nullptr);
		assert(mHP != 0);
		assert(mDamage != 0);
		assert(mExp != 0);
		assert(std::abs(mSpeed) > FLT_EPSILON);
		assert(mpRightImage != nullptr);
		assert(mpLeftImage != nullptr);
		assert(mpRightDeathImage != nullptr);
		assert(mpLeftDeathImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		assert(mpExpGemObjPool != nullptr);
		assert(mpMonsterObjPool != nullptr);
		
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpCollider->SetColliderLayer(eColliderLayer::MONSTER);
		mpAnimator->CreateAnimation(mImageRightMoveKey, mpRightImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimImageCount, mAnimDuration);
		mpAnimator->CreateAnimation(mImageLeftMoveKey, mpLeftImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimImageCount, mAnimDuration);
		mpAnimator->CreateAnimation(mImageRightDeathKey, mpRightDeathImage, Vector2::ZERO, mAnimDeathSize, mAnimOffset, mAnimDeathImageCount, mAnimDuration);
		mpAnimator->CreateAnimation(mImageLeftDeathKey, mpLeftDeathImage, Vector2::ZERO, mAnimDeathSize, mAnimOffset, mAnimDeathImageCount, mAnimDuration);

		mpAnimator->Play(mImageRightDeathKey, false);
		//mPlayerPos = mpPlayer->GetPos();
	}

	void Monster::Tick()
	{
		GameObject::Tick();
		assert(mpPlayer != nullptr);

		if (mbIsDeathFromWeapon)
		{
			mAnimDeathCounter -= Time::DeltaTime();
			if (meLookDir == eMonsterLookDir::LEFT)
				{mpAnimator->Play(mImageLeftDeathKey, false);}
			else
				{mpAnimator->Play(mImageRightDeathKey, false);}

			if (mAnimDeathCounter <= 0.0f)
			{
				mpMonsterObjPool->Return(this);
				return;
			}
			return;
		}

		mPlayerPos = mpPlayer->GetPos();
		float diffX = mPos.x - mPlayerPos.x;
		if (diffX < 0.0f)
		{
			meLookDir = eMonsterLookDir::RIGHT;
			mpAnimator->Play(mImageRightMoveKey, true);
		}
		else
		{
			meLookDir = eMonsterLookDir::LEFT;
			mpAnimator->Play(mImageLeftMoveKey, true);
		}
	}

	Monster::~Monster()
	{
	}


	void Monster::OnCollisionEnter(Collider* pCollider)
	{
		switch (pCollider->GetColliderLayer())
		{
		case eColliderLayer::PLAYER_PROJECTTILE:
		{
			Weapon* pWeapon = static_cast<Weapon*>(pCollider->GetOwner());
			mHP -= pWeapon->GetDamage();
			if (mHP <= 0)
			{
				mbIsDeathFromWeapon = true;
				PlayScene* pScene = static_cast<PlayScene*>(SceneManager::GetCurrentScene());
				ExpGem* pExpGem = mpExpGemObjPool->Get(mPos, mpPlayer, mExp, mpExpGemObjPool);
				pScene->AddGameObject(pExpGem, eColliderLayer::EXP_JEM);
				mpCollider->SetSize(Vector2(0.0f, 0.0f));

			}
			break;
		}
		default:
			break;
		}
	}
	void Monster::OnCollisionStay(Collider* pCollider)
	{
		if (pCollider->GetSize() == Vector2::ZERO)
		{
			return;
		}
		if (pCollider->GetColliderLayer() == eColliderLayer::MONSTER)
		{
			GameObject* pOtherObject = pCollider->GetOwner();
			Vector2 myCollderSize = mpCollider->GetSize();
			Vector2 otherColliderSize = pCollider->GetSize();
			Vector2 objPos = pOtherObject->GetPos();

			GameObject* pFixedObject;
			GameObject* pMovingObject;

			float myLeftTopX = mPos.x - myCollderSize.x / 2;
			float myRightBottomX = mPos.x + myCollderSize.x / 2;

			float otherLeftTopX = objPos.x - otherColliderSize.x / 2;
			float otherRightBottomX = objPos.x + otherColliderSize.x / 2;

			float pushXLength = 0.0f;

			if (myLeftTopX <= otherLeftTopX)
			{
				pFixedObject = this;
				pMovingObject = pOtherObject;
				pushXLength = myRightBottomX - otherLeftTopX;
			}
			else
			{
				pFixedObject = pOtherObject;
				pMovingObject = this;
				pushXLength = otherRightBottomX - myLeftTopX;
			}

			pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x + pushXLength * mSpeed * Time::DeltaTime(), pMovingObject->GetPos().y));


			//float myLeftTopY = mPos.y - myCollderSize.y / 2;
			//float myRightBottomY = mPos.y + myCollderSize.y / 2;

			//float otherLeftTopY = objPos.y - otherColliderSize.y / 2;
			//float otherRightBottomY = objPos.y + otherColliderSize.y / 2;

			//// my의 오른쪽 y좌표가 other의 오른족 y좌표보다 위에 있으면
			//float pushYlengh = 0.0f;
			//// TODO : 여기를 고쳐보자
			//if (myLeftTopY <= otherLeftTopY)
			//{
			//	pFixedObject = this;
			//	pMovingObject = pOtherObject;
			//	pushYlengh = -(otherLeftTopY - myRightBottomY);
			//}
			//// my의 오른쪽 y좌표가 other의 오른족 y좌표보다 아래에 있으면
			//else
			//{
			//	pFixedObject = pOtherObject;
			//	pMovingObject = this;
			//	pushYlengh = -(myLeftTopY - otherRightBottomY);
			//}

			////assert(std::abs(pushXLength) > FLT_EPSILON && std::abs(pushYlengh) > FLT_EPSILON);
			//pMovingObject->SetPos(Vector2(pMovingObject->GetPos().x, pMovingObject->GetPos().y + pushYlengh * mSpeed * Time::DeltaTime()));
		}
	}
	void Monster::OnCollisionExit(Collider* pCollider)
	{
	}
}