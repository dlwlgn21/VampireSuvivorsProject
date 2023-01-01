#pragma once
#include "yaComponent.h"

namespace ya
{
	class Component;
	class Collider final : public Component
	{
	public:
		Collider();
		Collider(Vector2 size);
		Collider(Vector2 size, eColliderLayer eColliderLayer);
		~Collider();

		void Tick() override;
		void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

		__forceinline void SetOffset(Vector2 offset) { mOffset = offset; }
		__forceinline void SetPos(Vector2 pos) { mPos = pos; }
		__forceinline void SetSize(Vector2 size) { mSize = size; }

		__forceinline Vector2 GetOffset() const { return mOffset; }
		__forceinline Vector2 GetPos() const { return mPos; }
		__forceinline Vector2 GetSize() const { return mSize; }

		__forceinline void SetColliderLayer(eColliderLayer layer) { meLayerType = layer; }
		__forceinline eColliderLayer GetColliderLayer() const { return meLayerType; }

	private:
		Vector2 mOffset;
		Vector2 mPos;
		Vector2 mSize;

		eColliderLayer meLayerType;
		unsigned char mCollisionCount;
	};
}