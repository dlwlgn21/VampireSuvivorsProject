#include "yaMissile.h"
#include "yaTime.h"
#include "yaImage.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaAnimator.h"
#include "yaAnimation.h"
#include "yaResources.h"
#include "yaInput.h"

namespace ya
{
	Missile::Missile()
		: GameObject()
		, mSpeed(200.0f)
		, mLifeTime(3.0f)
		, mpImage(nullptr)
		, mDir(Vector2::UP)
		, mDestPos(Vector2::ZERO)
	{
		SetScale({ 1.0f, 1.0f });
		AddComponent(new Collider(GetScale()));

		mpImage = Resources::Load<Image>(L"MissleIdleAnim", L"Resources\\Image\\link.bmp");
		assert(mpImage != nullptr);
		mpAnimator = new Animator();
		AddComponent(mpAnimator);
		mpAnimator->CreateAnimation(
			L"MissleIdleAnim",
			mpImage,
			Vector2(0.0f, 0.0f),
			Vector2(120.0f, 130.0f),
			Vector2(0.0f, 0.0f),
			3,
			0.1f
		);

		mpAnimator->Play(L"MissleIdleAnim", true);
	}

	Missile::~Missile()
	{
	}
	void Missile::Tick()
	{
		GameObject::Tick();

		//float degree = DegreeToRad(180.0f);
		//mPos.x += mSpeed * cosf(Vector2::UP.x) * Time::DeltaTime();
		//mPos.y -= mSpeed * sinf(Vector2::UP.y) * Time::DeltaTime();
		//Vector2 mousePos = Input::GetMousePos();

		//mDir = mDestPos - mPos;
		//mDir.Normalize();

		mPos.x += mDir.x * mSpeed * Time::DeltaTime();
		mPos.y += mDir.y * mSpeed * Time::DeltaTime();
		mLifeTime -= Time::DeltaTime();
		if (mLifeTime <= 0.0f)
		{
			this->DisableObject();
		}
	}

	void Missile::Render(HDC hdc)
	{
		//Vector2 pos = Camera::ToCameraPos(mPos);
		//Ellipse(
		//	hdc, 
		//	static_cast<int>(pos.x - mScale.x),
		//	static_cast<int>(pos.y - mScale.y),
		//	static_cast<int>(pos.x + mScale.x),
		//	static_cast<int>(pos.y + mScale.y)
		//);
		GameObject::Render(hdc);

	}
	void Missile::OnCollisionEnter(Collider* other)
	{
		GameObject* object = other->GetOwner();
		object->DisableObject();
		DisableObject();
	}
	void Missile::OnCollisionStay(Collider* other)
	{
	}
	void Missile::OnCollisionExit(Collider* other)
	{
	}
}
