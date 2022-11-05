#include "yaCollider.h"
#include "yaGameObejct.h"
#include "yaApplication.h"
#include "yaCamera.h"


namespace ya
{
	Collider::Collider(Vector2 scale)
		: Component(eComponentType::COLLIDER)
		, mPos(Vector2::ZERO)
		, mScale(scale)
		, mOffset(Vector2::ZERO)
		, mCollisionCount(0)
	{
	}
	Collider::Collider()
		: Component(eComponentType::COLLIDER)
		, mPos(Vector2::ZERO)
		, mScale(Vector2::ONE)
		, mOffset(Vector2::ZERO)
		, mCollisionCount(0)
	{
		mScale = Vector2(100.0f, 100.0f);
	}
	Collider::~Collider()
	{
	}

	void Collider::Tick()
	{
		GameObject* owner = GetOwner();
		mPos = owner->GetPos() + mOffset;
	}
	void Collider::Render(HDC hdc)
	{
		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN prevPen = NULL;

		HBRUSH transBrush = Application::GetInstance().GetBrush(eBrushColor::TRANS_PARENT);
		Brush brush(hdc, transBrush);

		if (mCollisionCount > 0)
		{
			prevPen = static_cast<HPEN>(SelectObject(hdc, redPen));
		}
		else
		{
			prevPen = static_cast<HPEN>(SelectObject(hdc, greenPen));
		}
		Vector2 fPos;
		fPos.x = mPos.x - mScale.x / 2;
		fPos.y = mPos.y - mScale.y / 2;
		Vector2 fScale;
		fScale.x = mPos.x + mScale.x / 2;
		fScale.y = mPos.y + mScale.y / 2;
		fPos = Camera::ToCameraPos(fPos);
		fScale = Camera::ToCameraPos(fScale);
		Rectangle(
			hdc,
			static_cast<int>(fPos.x),
			static_cast<int>(fPos.y),
			static_cast<int>(fScale.x),
			static_cast<int>(fScale.y)
		);
		SelectObject(hdc, prevPen);
		DeleteObject(redPen);
		DeleteObject(greenPen);
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		++mCollisionCount;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		--mCollisionCount;
		GetOwner()->OnCollisionExit(other);
	}
}