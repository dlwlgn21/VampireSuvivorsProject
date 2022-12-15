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
		: Weapon(eWeaponPenetratingType::COMPLETE_PENETRATING, spawanPos, damage, speed, knockBackValue, shootInterval)
		, mpRuneTracerImage(Resources::Load<Image>(L"RuneTracer", L"Resources\\Image\\RuneTracer.bmp"))
		, mSizeX(mpRuneTracerImage->GetWidth())
		, mSizeY(mpRuneTracerImage->GetHeight())
		, mpPool(pPool)
		, mDegree(0.0f)
		, mRotatedVector(Vector2::ZERO)
		, meRuneQudrant(eRuneQudrant::COUNT)
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
		std::uniform_int_distribution<> degreeDist(1, 360);

		mDegree = static_cast<float>(degreeDist(gen));
		//wchar_t buffer[128];
		//swprintf_s(buffer, 128, L"mDegree is %f\nmPos is {%f, %f}\n", mDegree, mPos.x, mPos.y);
		//OutputDebugStringW(buffer);
		if (mDegree >= 75.0f && mDegree <= 90.0f)
		{
			mDegree = 75.0f;
		}
		else if (mDegree >= 165.0f && mDegree <= 180.0f)
		{
			mDegree = 165.0f;
		}
		else if (mDegree >= 255.0f && mDegree <= 270.0f)
		{
			mDegree = 255.0f;
		}
		else if (mDegree >= 345.0f && mDegree <= 360.0f)
		{
			mDegree = 345.0f;
		}

		float sin, cos;
		yamath::GetSinCosValueAtDegree(sin, cos, mDegree);
		mRotatedVector = { (mPos.x * cos) - (mPos.y * sin), (mPos.x * cos) + (mPos.y + sin) };
		
		// Quadrant 2
		if (mDegree < 90.0f)
		{
			meRuneQudrant = eRuneQudrant::QUDRANT_1;
		}
		// Qudrant 3
		else if (mDegree < 180.0f)
		{
			meRuneQudrant = eRuneQudrant::QUDRANT_2;
		}
		// Qudrant 1
		else if (mDegree < 270.0f)
		{
			meRuneQudrant = eRuneQudrant::QUDRANT_3;
		}
		// Qudrant 4
		else if (mDegree < 360.0f)
		{
			meRuneQudrant = eRuneQudrant::QUDRANT_4;
		}

		assert(meRuneQudrant != eRuneQudrant::COUNT);

		wchar_t buffer[128];
		swprintf_s(buffer, 128, L"sin is %f, cos is %f || RotateVector is {%f, %f}\n", sin, cos, mRotatedVector.x, mRotatedVector.y);
		OutputDebugStringW(buffer);

		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		SetScale({ 2.0f, 2.0f });
		mpCollider->SetSize(GetSize());
	}
	void RuneTracer::Tick()
	{
		assert(std::abs(mDegree) >= FLT_EPSILON);
		Weapon::Tick();
		mShootTimer += Time::DeltaTime();
		if (mShootTimer >= mShootInterval)
		{
			mShootTimer = 0.0f;
			SetActive(false);
			mpPool->Return(this);
			return;
		}

		float x = mRotatedVector.x - mPos.x;
		float y = mRotatedVector.y - mPos.y;
		
		//Get Slope
		float m;
		if (std::abs(x) <= FLT_EPSILON)
		{
			m = 1.0f;
		}
		if (std::abs(y) <= FLT_EPSILON)
		{
			m = -1.0f;
		}
		m = y / x;
		if (m > 1.0f)
		{
			m = 1.0f;
		}
		if (meRuneQudrant == eRuneQudrant::QUDRANT_1)
		{
			mPos.x += mSpeed * Time::DeltaTime();
			mPos.y -= mSpeed * m * Time::DeltaTime();
		}
		else if (meRuneQudrant == eRuneQudrant::QUDRANT_2)
		{
			mPos.x -= mSpeed * Time::DeltaTime();
			mPos.y -= mSpeed * m * Time::DeltaTime();
		}
		else if (meRuneQudrant == eRuneQudrant::QUDRANT_3)
		{
			mPos.x -= mSpeed * Time::DeltaTime();
			mPos.y += mSpeed * m * Time::DeltaTime();
		}
		else if (meRuneQudrant == eRuneQudrant::QUDRANT_4)
		{
			mPos.x += mSpeed * Time::DeltaTime();
			mPos.y += mSpeed * m * Time::DeltaTime();
		}
		else
		{
			assert(false);
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
		std::uniform_int_distribution<> dist(-30, 30);
		mPos.x += static_cast<float>(dist(gen));
		mPos.y += static_cast<float>(dist(gen));
		std::uniform_int_distribution<> degreeDist(1, 360);
		mDegree = static_cast<float>(degreeDist(gen));

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

		float sin, cos;
		yamath::GetSinCosValueAtDegree(sin, cos, mDegree);
		mRotatedVector = { (mPos.x * cos) - (mPos.y * sin), (mPos.x * cos) + (mPos.y + sin) };


		wchar_t buffer[128];
		// Quadrant 2
		if (mDegree <= 90.0f)
		{
			meRuneQudrant = eRuneQudrant::QUDRANT_1;
			swprintf_s(buffer, 128, L"Qudrant_2\n");
			OutputDebugStringW(buffer);
		}
		// Qudrant 3
		else if (mDegree <= 180.0f)
		{
			meRuneQudrant = eRuneQudrant::QUDRANT_2;
			swprintf_s(buffer, 128, L"Qudrant_3\n");
			OutputDebugStringW(buffer);
		}
		// Qudrant 1
		else if (mDegree <= 270.0f)
		{
			meRuneQudrant = eRuneQudrant::QUDRANT_3;
			swprintf_s(buffer, 128, L"Qudrant_1\n");
			OutputDebugStringW(buffer);
		}
		// Qudrant 4
		else if (mDegree <= 360.0f)
		{
			meRuneQudrant = eRuneQudrant::QUDRANT_4;
			swprintf_s(buffer, 128, L"Qudrant_1\n");
			OutputDebugStringW(buffer);
		}
		assert(meRuneQudrant != eRuneQudrant::COUNT);

		swprintf_s(buffer, 128, L"mDegree is %f\n", mDegree);
		OutputDebugStringW(buffer);
		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		SetScale({ 2.0f, 2.0f });
		mpCollider->SetSize(GetSize());
	}
}
