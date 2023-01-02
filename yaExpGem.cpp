#include "yaExpGem.h"
#include "yaImage.h"
#include "yaCollider.h"
#include "yaResources.h"
#include "yaCamera.h"
#include "yaPlayer.h"
#include "yaExpGemObjPool.h"

namespace ya
{
	ExpGem::ExpGem(Vector2 pos, Player* pPlayer, int exp, ExpGemObjPool* pObjPool)
		: GameObject(pos)
		, mpPlayer(pPlayer)
		, mpImage(Resources::Load<Image>(L"BlueExpGem", L"Resources\\Image\\BlueExpGem.bmp"))
		, mImgWidth(mpImage->GetWidth())
		, mImgHeight(mpImage->GetHeight())
		, mExp(exp)
		, mpCollider(new Collider(Vector2( static_cast<float>(mImgWidth), static_cast<float>(mImgHeight)), eColliderLayer::EXP_JEM))
		, mBlendFunc{}
		, mpPool(pObjPool)
	{
		assert(mpPlayer != nullptr);
		assert(mpImage != nullptr);
		assert(mpCollider != nullptr);
		assert(mExp != 0);
		AddComponent(mpCollider);
		mBlendFunc.BlendOp = AC_SRC_OVER;
		mBlendFunc.BlendFlags = 0;
		mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
		mBlendFunc.SourceConstantAlpha = 255;
	}
	void ExpGem::Tick()
	{
		GameObject::Tick();
	}
	void ExpGem::Render(HDC hdc)
	{
		Vector2 pos = Camera::ToCameraPos(mPos);
		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mImgWidth / 2.0f),
			static_cast<int>(pos.y - mImgHeight / 2.0f),
			static_cast<int>(mImgWidth * mScale.x),
			static_cast<int>(mImgHeight * mScale.y),

			mpImage->GetDC(),
			0,
			0,
			mImgWidth,
			mImgHeight,
			mBlendFunc
		);
		GameObject::Render(hdc);
	}
	void ExpGem::OnCollisionEnter(Collider* pCollider)
	{
		if (pCollider != nullptr && pCollider->GetColliderLayer() == eColliderLayer::PLAYER)
		{
			mpPlayer->IncreaseExp(mExp);
			mpPool->Return(this);
		}
	}
	void ExpGem::OnCollisionStay(Collider* pCollider)
	{
	}
	void ExpGem::OnCollisionExit(Collider* pCollider)
	{
	}
}