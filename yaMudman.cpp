#include "yaMudman.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaImage.h"
#include "yaCamera.h"
#include "yaPlayer.h"
#include "yaTime.h"
#include "yaWeapon.h"
#include "yaExpGem.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"

namespace ya
{
	Mudman::Mudman(Vector2 pos, Player* pPlayer)
		: Monster(pos, pPlayer, MUDMAN_INITIAL_HP, MUDMAN_INITIAL_DAMAGE, ONE_MIN_NORMAL_MONSTER_EXP, 200.0f)
		, mpImage(Resources::Load<Image>(L"Mudman", L"Resources\\Image\\MudmanAnim.bmp"))
		, mpInvImage(Resources::Load<Image>(L"MudmanInv", L"Resources\\Image\\MudmanInvAnim.bmp"))
		, mpLeftDeathImage(Resources::Load<Image>(L"MudmanLDeath", L"Resources\\Image\\MudManLeftDeathAnim.bmp"))
		, mpRightDeathImage(Resources::Load<Image>(L"MudmanRDeath", L"Resources\\Image\\MudManDeathRightAnim.bmp"))
		, mpAnimator(new Animator())
		, mpCollider(new Collider(Vector2(56.0f, 66.0f)))
		, mAnimMove(L"MudmanAnim")
		, mAnimInvMove(L"MudmanAnimInv")
		, mAnimLeftDeath(L"MudmanAnimLDeath")
		, mAnimRightDeath(L"MudmanAnimRDeath")
		, mAnimMoveSize(56.0f, 66.0f)
		, mAnimDeathSize(56.0f, 56.0f)
		, mAnimOffset(0.0f, 0.0f)
		, mAnimCount(5)
		, mAnimDuration(0.15f)
		, mDeathAnimCounter(mAnimDuration * 7)
		, mbIsDeathFromWeapon(false)
	{
		assert(mpImage != nullptr);
		assert(mpInvImage != nullptr);
		assert(mpLeftDeathImage != nullptr);
		assert(mpRightDeathImage != nullptr);
		assert(mpAnimator != nullptr);
		assert(mpCollider != nullptr);
		SetName(L"Mudman");
		AddComponent(mpAnimator);
		AddComponent(mpCollider);
		mpCollider->SetColliderLayer(eColliderLayer::MONSTER);
		mpAnimator->CreateAnimation(mAnimMove,	mpImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimInvMove, mpInvImage, Vector2::ZERO, mAnimMoveSize, mAnimOffset, mAnimCount, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimLeftDeath, mpLeftDeathImage, Vector2::ZERO, mAnimDeathSize, mAnimOffset, 7, mAnimDuration);
		mpAnimator->CreateAnimation(mAnimRightDeath, mpRightDeathImage, Vector2::ZERO, mAnimDeathSize, mAnimOffset, 7, mAnimDuration);
		mpAnimator->Play(mAnimInvMove, true);
	}

	void Mudman::Tick()
	{
		if (mbIsDeathFromWeapon)
		{
			mDeathAnimCounter -= Time::DeltaTime();
			if (mDeathAnimCounter <= 0.0f)
			{
				SetActive(false);
			}
		}
		Vector2 monDir = GetVectorToPlayer();
		monDir.Normalize();

		mPos.x += monDir.x * mSpeed * Time::DeltaTime();
		mPos.y += monDir.y * mSpeed * Time::DeltaTime();
		Monster::Tick();
	}
	void Mudman::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Mudman::OnCollisionEnter(Collider* pCollider)
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
				assert(mpPlayer != nullptr);
				PlayScene* pScene = static_cast<PlayScene*>(SceneManager::GetCurrentScene());
				ExpGem* pExpGem = new ExpGem(mPos, mpPlayer, EXP_BLUE_GEM);
				pScene->AddGameObject(pExpGem, eColliderLayer::EXP_JEM);
				mpAnimator->Play(mAnimRightDeath, false);
			}
			break;
		}
		default:
			break;
		}
	}
	void Mudman::OnCollisionStay(Collider* pCollider)
	{
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
	void Mudman::OnCollisionExit(Collider* pCollider)
	{
	}
}