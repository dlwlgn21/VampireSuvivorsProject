#include "yaRuneTracer.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaCamera.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaWeaponObjectPool.h"

namespace ya
{
	RuneTracer::RuneTracer(Vector2 spawanPos, int damage, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<RuneTracer>* pPool)
		: Weapon(eWeaponType::COMPLETE_PENETRATING, spawanPos, damage, speed, knockBackValue, shootInterval)
		, mpRuneTracerImage(Resources::Load<Image>(L"RuneTracer", L"Resources\\Image\\RuneTracer.bmp"))
		, mSizeX(mpRuneTracerImage->GetWidth())
		, mSizeY(mpRuneTracerImage->GetHeight())
		, mpPool(pPool)
	{
		assert(mpRuneTracerImage != nullptr);
		assert(mpPool != nullptr);
		assert(mSizeX != 0);
		assert(mSizeY != 0);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-30, 30);
		mPos.x += static_cast<float>(dist(gen));
		mPos.y += static_cast<float>(dist(gen));
		//mSizeX = mpRuneTracerImage->GetWidth();
		//mSizeY = mpRuneTracerImage->GetHeight();
		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		SetScale({ 2.0f, 2.0f });
		mpCollider->SetSize(GetSize());
	}
	void RuneTracer::Tick()
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
		mpCollider->SetPos({mPos.x + 6.0f, mPos.y + 6.0f});
	}

	void RuneTracer::Render(HDC hdc)
	{
		Vector2 pos = Camera::ToCameraPos(mPos);
		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mSizeX / 2.0f),
			static_cast<int>(pos.y - mSizeY / 2.0f),
			static_cast<int>(mSizeX * mScale.x),
			static_cast<int>(mSizeY * mScale.y),

			mpRuneTracerImage->GetDC(),
			0,
			0,
			mSizeX,
			mSizeY,
			mFunc
		);
		Weapon::Render(hdc);
	}
	void RuneTracer::OnCollisionEnter(Collider* other)
	{

	}
	void RuneTracer::OnCollisionStay(Collider* other)
	{

	}
	void RuneTracer::OnCollisionExit(Collider* other)
	{

	}
	void RuneTracer::Initialize(Vector2 pos)
	{
		mPos = pos;
	}
}
