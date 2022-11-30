#pragma once
#include "yaWeapon.h"

namespace ya
{
	class Image;
	class RuneTracer final : public Weapon
	{
		RuneTracer(Vector2 spawanPos, int damage, float speed, float knockBackValue, float shootInterval);
		virtual ~RuneTracer() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void Initialize(Vector2 pos);

	private:
		Image* mpRuneTracerImage;
		int mSizeX;
		int mSizeY;
	};

}