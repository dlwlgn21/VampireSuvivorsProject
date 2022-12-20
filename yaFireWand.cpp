#include "yaFireWand.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaCamera.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaWeaponObjectPool.h"

namespace ya
{
	FireWand::FireWand(Vector2 spawanPos, int damage, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<FireWand>* pPool)
		: Weapon(eWeaponPenetratingType::COMPLETE_PENETRATING, spawanPos, damage, speed, knockBackValue, shootInterval)
		, mpFireImage(Resources::Load<Image>(L"WeaponFireWand", L"Resources\\Image\\Fire.bmp"))
		, mSizeX(mpFireImage->GetWidth())
		, mSizeY(mpFireImage->GetHeight())
		, mpPool(pPool)
	{
		assert(mpFireImage != nullptr);
		assert(mpPool != nullptr);
		assert(mSizeX != 0);
		assert(mSizeY != 0);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-30, 30);
		mPos.x += static_cast<float>(dist(gen));
		mPos.y += static_cast<float>(dist(gen));

		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		SetScale({ 2.0f, 2.0f });
		mpCollider->SetSize(GetSize() * 1.5f);
	}
	void FireWand::Tick()
	{
		Weapon::Tick();
		mShootTimer += Time::DeltaTime();
		if (mShootTimer >= mShootInterval)
		{
			mShootTimer = 0.0f;
			SetActive(false);
			mpPool->Return(this);
			return;
		}

		mPos.x += mSpeed * Time::DeltaTime();

		mpCollider->SetPos({ mPos.x + 8.0f, mPos.y + 8.0f });

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
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-30, 30);
		mPos.x += static_cast<float>(dist(gen));
		mPos.y += static_cast<float>(dist(gen));
		std::uniform_int_distribution<> degreeDist(1, 360);

		//if (mDegree >= 75.0f && mDegree <= 90.0f)
		//{
		//	mDegree = 75.0f;
		//}
		//else if (mDegree >= 165.0f && mDegree <= 180.0f)
		//{
		//	mDegree = 165.0f;
		//}
		//else if (mDegree >= 255.0f && mDegree <= 270.0f)
		//{
		//	mDegree = 255.0f;
		//}
		//else if (mDegree >= 345.0f && mDegree <= 360.0f)
		//{
		//	mDegree = 345.0f;
		//}

		//wchar_t buffer[128];
		//swprintf_s(buffer, 128, L"mDegree is %f\nmPos is {%f, %f}\n", mDegree, mPos.x, mPos.y);
		//OutputDebugStringW(buffer);

		//SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		//SetScale({ 2.0f, 2.0f });
		//mpCollider->SetSize(GetSize());
	}
}