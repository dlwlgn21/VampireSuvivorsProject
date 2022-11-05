#pragma once
#include "yaComponent.h"

namespace ya
{
	class Component;
	class Collider : public Component
	{
	public:
		Collider();
		Collider(Vector2 scale);
		~Collider();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		__forceinline void SetOffset(Vector2 offset) { mOffset = offset; }
		__forceinline void SetPos(Vector2 pos) { mPos = pos; }
		__forceinline void SetScale(Vector2 scale) { mScale = scale; }

		__forceinline Vector2 GetOffset() { return mOffset; }
		__forceinline Vector2 GetPos() { return mPos; }
		__forceinline Vector2 GetScale() { return mScale; }

	private:
		Vector2 mOffset;
		Vector2 mPos;
		Vector2 mScale;

		char mCollisionCount;
	};
}