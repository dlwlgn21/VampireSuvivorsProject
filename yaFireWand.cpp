#define SPREAD_DEGREE (5.0f)
#include "yaFireWand.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaCamera.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaWeaponObjectPool.h"

namespace ya
{
	FireWand::FireWand(Vector2 spawanPos, int damage, int penetratingCount, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<FireWand>* pPool)
		: Weapon(spawanPos, damage, penetratingCount, speed, knockBackValue, shootInterval)
		, mpFireImage(Resources::Load<Image>(L"WeaponFireWand", L"Resources\\Image\\Fire.bmp"))
		, mSizeX(mpFireImage->GetWidth())
		, mSizeY(mpFireImage->GetHeight())
		, mpPool(pPool)
		, mVelocityX(0.0f)
		, mVelocityY(0.0f)
		, mIdx(0u)
	{
		assert(mpFireImage != nullptr);
		assert(mpPool != nullptr);
		assert(mSizeX != 0);
		assert(mSizeY != 0);
		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		initAndSetVelocity();
		mpCollider->SetSize(GetSize());
	}
	void FireWand::Tick()
	{
		Weapon::Tick();
		mDurationTimer += Time::DeltaTime();
		if (mDurationTimer >= mWeaponDuration)
		{
			mDurationTimer = 0.0f;
			SetActive(false);
			mpPool->Return(this);
			return;
		}

		mPos.x += mVelocityX * Time::DeltaTime();
		mPos.y += mVelocityY * Time::DeltaTime();

		mpCollider->SetPos({ mPos.x, mPos.y });

	}

	void FireWand::Render(HDC hdc)
	{
		Vector2 pos = Camera::ToCameraPos(mPos);
		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mSizeX / 2.0f),
			static_cast<int>(pos.y - mSizeY / 2.0f),
			static_cast<int>(mSizeX * mScale.x),
			static_cast<int>(mSizeY * mScale.y),

			mpFireImage->GetDC(),
			0,
			0,
			mSizeX,
			mSizeY,
			mFunc
		);
		Weapon::Render(hdc);
	}
	void FireWand::OnCollisionEnter(Collider* other)
	{
		if (other != nullptr && other->GetColliderLayer() == eColliderLayer::MONSTER)
		{
			//Monster* pMonster = static_cast<Monster*>(other->GetOwner());
			//pMonster->DamagedFromWeapon(mDamage);
			SetActive(false);
			mpPool->Return(this);
			// Vector2 monPos = pMonster->GetPos(); 
		}
	}
	void FireWand::OnCollisionStay(Collider* other)
	{

	}
	void FireWand::OnCollisionExit(Collider* other)
	{

	}
	void FireWand::Initialize(Vector2 pos)
	{
		mPos = pos;
		initAndSetVelocity();
		mpCollider->SetIsWorking(true);
	}
	void FireWand::initAndSetVelocity()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-30, 30);
		//mPos.x += static_cast<float>(dist(gen));
		//mPos.y += static_cast<float>(dist(gen));
		assert(mIdx <= 4);
		float degree = -35.0f;
	
		degree -= SPREAD_DEGREE * mIdx;
		
		float c = std::cosf(yamath::DegreeToRad(degree));
		float s = std::sinf(yamath::DegreeToRad(degree));

		mVelocityX = mSpeed * c - mSpeed * s;
		mVelocityY = mSpeed * s + mSpeed * c;
	}
}