#pragma once
#include "yaComponent.h"

namespace ya
{
	class Component;
	class Collider final : public Component
	{
	public:
		Collider();
		Collider(Vector2 scale);
		~Collider();

		void Tick() override;
		void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

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