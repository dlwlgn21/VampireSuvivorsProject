#include "yaCollider.h"
#include "yaGameObejct.h"
#include "yaApplication.h"
#include "yaCamera.h"


namespace ya
{
	Collider::Collider(Vector2 size)
		: Component(eComponentType::COLLIDER)
		, mPos(Vector2::ZERO)
		, mSize(size)
		, mOffset(Vector2::ZERO)
		, mCollisionCount(0)
	{
	}
	Collider::Collider(Vector2 size, eColliderLayer eColliderLayer)
		: Component(eComponentType::COLLIDER)
		, mPos(Vector2::ZERO)
		, mSize(size)
		, mOffset(Vector2::ZERO)
		, mCollisionCount(0)
		, meLayerType(eColliderLayer)
	{
	}

	Collider::Collider()
		: Component(eComponentType::COLLIDER)
		, mPos(Vector2::ZERO)
		, mSize(Vector2::ONE)
		, mOffset(Vector2::ZERO)
		, mCollisionCount(0)
	{
		mSize = Vector2(100.0f, 100.0f);
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
			{ prevPen = static_cast<HPEN>(SelectObject(hdc, redPen)); }
		else
			{ prevPen = static_cast<HPEN>(SelectObject(hdc, greenPen)); }


		Vector2 leftTop(mPos.x - mSize.x / 2, mPos.y - mSize.y / 2);
		Vector2 rightBottom(mPos.x + mSize.x / 2, mPos.y + mSize.y / 2);
		leftTop = Camera::ToCameraPos(leftTop);
		rightBottom = Camera::ToCameraPos(rightBottom);

		Rectangle(
			hdc,
			static_cast<int>(leftTop.x),
			static_cast<int>(leftTop.y),
			static_cast<int>(rightBottom.x),
			static_cast<int>(rightBottom.y)
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