const constexpr unsigned int ACCEL_MIN = 5;
const constexpr unsigned int ACCEL_MAX = 15;
#include "yaAxe.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaCamera.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaWeaponObjectPool.h"

namespace ya
{
	Axe::Axe(Vector2 spawanPos, int damage, int penetratingCount, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<Axe>* pPool)
		: Weapon(spawanPos, damage, penetratingCount, speed, knockBackValue, shootInterval)
		, mpAxeImage(Resources::Load<Image>(L"WeaponAxe", L"Resources\\Image\\Axe.bmp"))
		, mSizeX(mpAxeImage->GetWidth())
		, mSizeY(mpAxeImage->GetHeight())
		, mVelocityX(mSpeed)
		, mVelocityY(mSpeed)
		, M_INITIAL_SPEED(mSpeed)
		, mAccel(0.0f)
		, mpPool(pPool)
	{
		assert(mpAxeImage != nullptr);
		assert(mpPool != nullptr);
		assert(mSizeX != 0);
		assert(mSizeY != 0);
		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		initPosAndAccel();
		mpCollider->SetSize(GetSize());
	}
	void Axe::Tick()
	{
		Weapon::Tick();
		mDurationTimer += Time::DeltaTime();

		if (mDurationTimer >= mWeaponDuration)
		{
			mDurationTimer = 0.0f;
			mpPool->Return(this);
			return;
		}

		mVelocityY += mAccel;
		mPos.x += mVelocityX * Time::DeltaTime();
		mPos.y += mVelocityY * Time::DeltaTime();
		mpCollider->SetPos({ mPos.x, mPos.y});
	}

	void Axe::Render(HDC hdc)
	{
		Vector2 pos = Camera::ToCameraPos(mPos);
		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mSizeX / 2.0f),
			static_cast<int>(pos.y - mSizeY / 2.0f),
			static_cast<int>(mSizeX * mScale.x),
			static_cast<int>(mSizeY * mScale.y),

			mpAxeImage->GetDC(),
			0,
			0,
			mSizeX,
			mSizeY,
			mFunc
		);
		Weapon::Render(hdc);
	}
	void Axe::OnCollisionEnter(Collider* other)
	{
		if (other != nullptr && other->GetColliderLayer() == eColliderLayer::MONSTER)
		{
			--mPenetratingCounter;
			if (mPenetratingCounter <= 0)
			{
				mpPool->Return(this);
				return;
			}
		}
	}
	void Axe::OnCollisionStay(Collider* other)
	{

	}
	void Axe::OnCollisionExit(Collider* other)
	{

	}
	void Axe::Initialize(Vector2 pos)
	{
		mPos = pos;
		initPosAndAccel();
		mpCollider->SetPos(pos);
	}
	void Axe::initPosAndAccel()
	{
		assert(std::abs(mSpeed) > FLT_EPSILON);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> xDist(-30, 30);
		std::uniform_int_distribution<> yDist(-50, -15);
		std::uniform_int_distribution<> accelDist(5, 15);
		std::uniform_int_distribution<> speedDist(static_cast<int>(M_INITIAL_SPEED + 200), static_cast<int>(M_INITIAL_SPEED + 500));
		mSpeed = static_cast<float>(speedDist(gen));
		mPos.x += static_cast<float>(xDist(gen));
		mPos.y += static_cast<float>(yDist(gen));
		mAccel = static_cast<float>(accelDist(gen));
		if (static_cast<int>(mAccel) <= (ACCEL_MIN + ACCEL_MAX) / 2)
		{
			mVelocityX = -mVelocityX;
		}
		mVelocityY = -mSpeed - mAccel;
		mPenetratingCounter = mPenetratingCount;
	}
}