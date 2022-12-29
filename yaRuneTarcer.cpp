#include "yaRuneTracer.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaCamera.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaWeaponObjectPool.h"
#include "yaGameMapCollider.h"

namespace ya
{
	RuneTracer::RuneTracer(Vector2 spawanPos, int damage, int penetratingCount, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<RuneTracer>* pPool)
		: Weapon(spawanPos, damage, penetratingCount, speed, knockBackValue, shootInterval)
		, mpRuneTracerImage(Resources::Load<Image>(L"WeaponRuneTracer", L"Resources\\Image\\RuneTracer.bmp"))
		, mSizeX(mpRuneTracerImage->GetWidth())
		, mSizeY(mpRuneTracerImage->GetHeight())
		, mpPool(pPool)
		, mVelocityX(0.0f)
		, mVelocityY(0.0f)
	{
		assert(mpRuneTracerImage != nullptr);
		assert(mpPool != nullptr);
		assert(mSizeX != 0);
		assert(mSizeY != 0);
		SetSize({ static_cast<float>(mSizeX), static_cast<float>(mSizeY) });
		setVelocity();
		mpCollider->SetSize(GetSize());
	}
	void RuneTracer::Tick()
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
		Vector2 cameraPos = Camera::ToCameraPos(mPos);
		if (cameraPos.x <= CAMERA_MASK_WIDTH || cameraPos.x >= SCREEN_WIDTH - CAMERA_MASK_WIDTH)
			{ changeHorizontalDirection(); }

		if (cameraPos.y <= EXP_BAR_HEIGHT || cameraPos.y >= SCREEN_HEIGHT)
			{ changeVerticalDirection(); }

		mPos.x += mVelocityX * Time::DeltaTime();
		mPos.y += mVelocityY * Time::DeltaTime();

		mpCollider->SetPos( {mPos.x, mPos.y} );
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
		if (other->GetColliderLayer() == eColliderLayer::BACKGROUND)
		{ 
			GameMapCollider* pGameMapCollider = static_cast<GameMapCollider*>(other->GetOwner());
			if (pGameMapCollider->GetMapColliderType() == eMapColliderType::LEFT_SCROLL_CHECKER || pGameMapCollider->GetMapColliderType() == eMapColliderType::RIGHT_SCROLL_CHECKER)
				{ return; }
			changeVerticalDirection(); 
		}

		if (other != nullptr && other->GetColliderLayer() == eColliderLayer::MONSTER)
		{
			//Monster* pMonster = static_cast<Monster*>(other->GetOwner());
			//pMonster->DamagedFromWeapon(mDamage);
			// Vector2 monPos = pMonster->GetPos();
		}
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
		setVelocity();
	}
	
	void RuneTracer::setVelocity()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 360);
		int degree = dist(gen);
		if (degree % 90 == 0)
		{
			degree -= 5;
		}
		float rad = yamath::DegreeToRad(static_cast<float>(degree));
		//mVelocityX = std::cosf(static_cast<float>(degree)) * mSpeed;
		//mVelocityY = std::sinf(static_cast<float>(degree)) * mSpeed;		
		mVelocityX = std::cosf(rad) * mSpeed;
		mVelocityY = std::sinf(rad) * mSpeed;
	}
}
