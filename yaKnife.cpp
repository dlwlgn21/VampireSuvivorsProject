#include "yaKnife.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaCamera.h"
#include "yaCollider.h"
#include "yaMonster.h"
#include "yaKnifeObjectPool.h"

namespace ya
{
	Knife::Knife(Vector2 spwanPos, int damage, float speed, float knockBackValue, float shootInterval, eKnifeDirection dir, KnifeObjectPool* pPool)
		: Weapon(eWeaponType::NO_PENETRATING, spwanPos, damage, speed, knockBackValue, shootInterval)
		, mpKnifeImage(nullptr)
		, mKnifeDirection(dir)
		, mpKnifeObjPool(pPool)
	{
		switch (mKnifeDirection)
		{
		case eKnifeDirection::UP:
			mpKnifeImage = Resources::Load<Image>(L"KnifeU", L"Resources\\Image\\KnifeU.bmp");
			break;
		case eKnifeDirection::DOWN:
			mpKnifeImage = Resources::Load<Image>(L"KnifeD", L"Resources\\Image\\KnifeD.bmp");
			break;
		case eKnifeDirection::LEFT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeL", L"Resources\\Image\\KnifeL.bmp");
			break;
		case eKnifeDirection::RIGHT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeR", L"Resources\\Image\\KnifeR.bmp");
			break;
		case eKnifeDirection::UP_LEFT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeUL", L"Resources\\Image\\KnifeUL.bmp");
			break;
		case eKnifeDirection::UP_RIGHT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeUR", L"Resources\\Image\\KnifeUR.bmp");
			break;
		case eKnifeDirection::DOWN_LEFT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeDL", L"Resources\\Image\\KnifeDL.bmp");
			break;
		case eKnifeDirection::DOWN_RIGHT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeDR", L"Resources\\Image\\KnifeDR.bmp");
			break;
		default:
			assert(false);
			break;
		}
		assert(mpKnifeImage != nullptr);
		assert(mpKnifeObjPool != nullptr);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-30, 30);
		mPos.x += static_cast<float>(dist(gen));
		mPos.y += static_cast<float>(dist(gen));
		mSizeX = mpKnifeImage->GetWidth();
		mSizeY = mpKnifeImage->GetHeight();
		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		SetScale({ 2.0f, 2.0f });
		mpCollider->SetSize(GetSize());
		
	}
	void Knife::Tick()
	{
		Weapon::Tick();
		mShootTimer += Time::DeltaTime();
		if (mShootTimer >= mShootInterval)
		{
			mShootTimer = 0.0f;
			SetActive(false);
			mpKnifeObjPool->Return(this);
			return;
		}
		switch (mKnifeDirection)
		{
		case eKnifeDirection::UP:
			mPos.y -= mSpeed * Time::DeltaTime();
			break;
		case eKnifeDirection::DOWN:
			mPos.y += mSpeed * Time::DeltaTime();
			break;
		case eKnifeDirection::LEFT:
			mPos.x -= mSpeed * Time::DeltaTime();
			break;
		case eKnifeDirection::RIGHT:
			mPos.x += mSpeed * Time::DeltaTime();
			break;
		case eKnifeDirection::UP_LEFT:
			mPos.x -= mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
			mPos.y -= mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
			break;
		case eKnifeDirection::UP_RIGHT:
			mPos.x += mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
			mPos.y -= mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
			break;
		case eKnifeDirection::DOWN_LEFT:
			mPos.x -= mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
			mPos.y += mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
			break;
		case eKnifeDirection::DOWN_RIGHT:
			mPos.x += mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
			mPos.y += mSpeed * Time::DeltaTime() * DIAGONAL_CORRECTION_VALUE;
			break;
		default:
			break;
		}
		mpCollider->SetPos({ mPos.x + 11.0f, mPos.y + 3.0f});
	}
	void Knife::Render(HDC hdc)
	{
		Vector2 pos = Camera::ToCameraPos(mPos);
		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mSizeX / 2.0f),
			static_cast<int>(pos.y - mSizeY / 2.0f),
			static_cast<int>(mSizeX * mScale.x),
			static_cast<int>(mSizeY * mScale.y),

			mpKnifeImage->GetDC(),
			0,
			0,
			mSizeX,
			mSizeY,
			mFunc
		);
		Weapon::Render(hdc);
	}
	void Knife::OnCollisionEnter(Collider* other)
	{
		if (other != nullptr)
		{
			Monster* pMonster = static_cast<Monster*>(other->GetOwner());
			pMonster->DamagedFromWeapon(mDamage);
		}
	}
	void Knife::OnCollisionStay(Collider* other)
	{
	}
	void Knife::OnCollisionExit(Collider* other)
	{
	}

	void Knife::Initialize(Vector2 pos, eKnifeDirection knifeDirection)
	{
		mKnifeDirection = knifeDirection;
		switch (mKnifeDirection)
		{
		case eKnifeDirection::UP:
			mpKnifeImage = Resources::Load<Image>(L"KnifeU", L"Resources\\Image\\KnifeU.bmp");
			break;
		case eKnifeDirection::DOWN:
			mpKnifeImage = Resources::Load<Image>(L"KnifeD", L"Resources\\Image\\KnifeD.bmp");
			break;
		case eKnifeDirection::LEFT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeL", L"Resources\\Image\\KnifeL.bmp");
			break;
		case eKnifeDirection::RIGHT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeR", L"Resources\\Image\\KnifeR.bmp");
			break;
		case eKnifeDirection::UP_LEFT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeUL", L"Resources\\Image\\KnifeUL.bmp");
			break;
		case eKnifeDirection::UP_RIGHT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeUR", L"Resources\\Image\\KnifeUR.bmp");
			break;
		case eKnifeDirection::DOWN_LEFT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeDL", L"Resources\\Image\\KnifeDL.bmp");
			break;
		case eKnifeDirection::DOWN_RIGHT:
			mpKnifeImage = Resources::Load<Image>(L"KnifeDR", L"Resources\\Image\\KnifeDR.bmp");
			break;
		default:
			assert(false);
			break;
		}
		assert(mpKnifeImage != nullptr);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-30, 30);
		mPos = pos;
		mPos.x += static_cast<float>(dist(gen));
		mPos.y += static_cast<float>(dist(gen));
		mSizeX = mpKnifeImage->GetWidth();
		mSizeY = mpKnifeImage->GetHeight();
		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		SetScale({ 2.0f, 2.0f });
		mpCollider->SetSize(GetSize());
	}
}