#include "yaBackpack.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	Backpack::Backpack()
		: GameObject()
		, mSpeed(200.0f)
		, mpImage(nullptr)
	{
		SetPos({ 250.0f, 250.0f });
		SetScale({ 3.0f, 3.0f });
		mpImage = Resources::Load<Image>(L"Backpack", L"Resources\\Image\\Backpack.bmp");
		assert(mpImage != nullptr);
		mFunc.BlendOp = AC_SRC_OVER;
		mFunc.BlendFlags = 0;
		mFunc.AlphaFormat = AC_SRC_ALPHA;
		mFunc.SourceConstantAlpha = 128;
	}

	Backpack::~Backpack()
	{
	}

	void Backpack::Tick()
	{
		GameObject::Tick();
	}

	void Backpack::Render(HDC hdc)
	{
		Vector2 fPos;
		fPos.x = mPos.x - mpImage->GetWidth() * (mScale.x / 2);
		fPos.y = mPos.y - mpImage->GetWidth() * (mScale.x / 2);
		fPos = Camera::ToCameraPos(fPos);
		AlphaBlend(
			hdc,
			static_cast<int>(fPos.x),
			static_cast<int>(fPos.y),
			static_cast<int>(mpImage->GetWidth() * mScale.x),
			static_cast<int>(mpImage->GetHeight() * mScale.y),

			mpImage->GetDC(),
			0, 0,
			mpImage->GetWidth(),
			mpImage->GetHeight(),
			mFunc
		);

		GameObject::Render(hdc);
	}
	void Backpack::OnCollisionEnter(Collider* other)
	{
		GameObject* object = other->GetOwner();
		object->DisableObject();
		DisableObject();
	}
	void Backpack::OnCollisionStay(Collider* other)
	{
	}
	void Backpack::OnCollisionExit(Collider* other)
	{
	}
}