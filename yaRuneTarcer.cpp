#include "yaRuneTracer.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaCamera.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaWeaponObjectPool.h"

namespace ya
{

	float RuneTracer::mDegrees[MAX_DEGREE_COUNT];

	RuneTracer::RuneTracer(Vector2 spawanPos, int damage, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<RuneTracer>* pPool)
		: Weapon(eWeaponPenetratingType::COMPLETE_PENETRATING, spawanPos, damage, speed, knockBackValue, shootInterval)
		, mpRuneTracerImage(Resources::Load<Image>(L"WeaponRuneTracer", L"Resources\\Image\\RuneTracer.bmp"))
		, mSizeX(mpRuneTracerImage->GetWidth())
		, mSizeY(mpRuneTracerImage->GetHeight())
		, mpPool(pPool)
		, mCurrDegreesIdx(0)
		, mSlope(0.0f)
		, mRotatedVector(Vector2::ZERO)
		, meRuneQudrant(eRuneQudrant::COUNT)
	{
		assert(mpRuneTracerImage != nullptr);
		assert(mpPool != nullptr);
		assert(mSizeX != 0);
		assert(mSizeY != 0);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, MAX_DEGREE_COUNT - 1);
		//std::uniform_int_distribution<> dist(0, 6);
		//std::uniform_int_distribution<> degreeDist(1, 360);
		//mPos.x += static_cast<float>(dist(gen));
		//mPos.y += static_cast<float>(dist(gen));

		mCurrDegreesIdx = dist(gen);
		assert(mCurrDegreesIdx <= MAX_DEGREE_COUNT - 1);

		//mDegree = static_cast<float>(degreeDist(gen));
		//wchar_t buffer[128];
		//swprintf_s(buffer, 128, L"mDegree is %f\nmPos is {%f, %f}\n", mDegree, mPos.x, mPos.y);
		//OutputDebugStringW(buffer);
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

		//float sin, cos;
		//yamath::GetSinCosValueAtDegree(sin, cos, mDegree);
		//mRotatedVector = { (mPos.x * cos) - (mPos.y * sin), (mPos.x * cos) + (mPos.y + sin) };
		//
		//// Quadrant 2
		//if (mDegree < 90.0f)
		//{
		//	meRuneQudrant = eRuneQudrant::QUDRANT_1;
		//}
		//// Qudrant 3
		//else if (mDegree < 180.0f)
		//{
		//	meRuneQudrant = eRuneQudrant::QUDRANT_2;
		//}
		//// Qudrant 1
		//else if (mDegree < 270.0f)
		//{
		//	meRuneQudrant = eRuneQudrant::QUDRANT_3;
		//}
		//// Qudrant 4
		//else if (mDegree < 360.0f)
		//{
		//	meRuneQudrant = eRuneQudrant::QUDRANT_4;
		//}

		//assert(meRuneQudrant != eRuneQudrant::COUNT);

		//wchar_t buffer[128];
		//swprintf_s(buffer, 128, L"sin is %f, cos is %f || RotateVector is {%f, %f}\n", sin, cos, mRotatedVector.x, mRotatedVector.y);
		//OutputDebugStringW(buffer);

		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		mRotatedVector = yamath::Rotate(mPos, mDegrees[mCurrDegreesIdx]);
		mSlope = std::tanf(yamath::DegreeToRad(mDegrees[mCurrDegreesIdx]));
		mPos = mRotatedVector;
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

		if (mCurrDegreesIdx <= 6)
		{
			mPos.x += mSpeed * Time::DeltaTime();
			mPos.y -= mSpeed * mSlope * Time::DeltaTime();
		}
		else if (mCurrDegreesIdx <= 13)
		{
			mPos.x -= mSpeed * Time::DeltaTime();
			mPos.y += mSpeed * mSlope * Time::DeltaTime();
		}
		else if (mCurrDegreesIdx <= 20)
		{
			mPos.x -= mSpeed * Time::DeltaTime();
			mPos.y -= mSpeed * mSlope * Time::DeltaTime();
		}
		else
		{
			mPos.x += mSpeed * Time::DeltaTime();
			mPos.y -= mSpeed * mSlope * Time::DeltaTime();
		}

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
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, MAX_DEGREE_COUNT - 1);
		//std::uniform_int_distribution<> dist(0, 6);
		mCurrDegreesIdx = dist(gen);
		wchar_t buffer[64];
		assert(mCurrDegreesIdx <= MAX_DEGREE_COUNT - 1);
		mpCollider->SetSize(GetSize());
		mRotatedVector = yamath::Rotate(mPos, mDegrees[mCurrDegreesIdx]);
		mSlope = std::tanf(yamath::DegreeToRad(mDegrees[mCurrDegreesIdx]));
		mPos = mRotatedVector;
		swprintf_s(buffer, 64, L"Idx : %d\nmPos.x{%1.f}, mPos.y{%1.f}\n", mCurrDegreesIdx, mRotatedVector.x, mRotatedVector.y);
		OutputDebugStringW(buffer);
	}

	void RuneTracer::InitializeDirVectors()
	{
		float degree = 10.0f;
		for (int i = 1; i <= MAX_DEGREE_COUNT; ++i)
		{
			mDegrees[i - 1] = degree;
			if (i % 7 == 0)
			{
				degree += 30.0f;
			}
			else
			{
				degree += 10.0f;
			}
		}
	}
}
