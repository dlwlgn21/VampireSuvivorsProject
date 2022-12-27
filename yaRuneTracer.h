#pragma once
#include "yaWeapon.h"
#include "yaWeaponObjectPool.h"
namespace ya
{
	class Image;
	template<typename T> class WeaponObjectPool;
	class RuneTracer final : public Weapon
	{
	public:
		friend class WeaponObjectPool<RuneTracer>;
		RuneTracer(Vector2 spawanPos, int damage, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<RuneTracer>* pPool);
		virtual ~RuneTracer() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void Initialize(Vector2 pos);

	private:
		void setVelocity();
		__forceinline void changeHorizontalDirection() { mVelocityX = -mVelocityX; }
		__forceinline void changeVerticalDirection() { mVelocityY = -mVelocityY; }

	private:
		Image* mpRuneTracerImage;
		WeaponObjectPool<RuneTracer>* mpPool;
		int mSizeX;
		int mSizeY;
		float mVelocityX;
		float mVelocityY;
	};

}