#pragma once
#include "yaWeapon.h"
#include "yaWeaponObjectPool.h"
namespace ya
{
	enum class eRuneQudrant
	{
		QUDRANT_1,
		QUDRANT_2,
		QUDRANT_3,
		QUDRANT_4,
		COUNT
	};

	class Image;
	template<typename T> class WeaponObjectPool;
	class RuneTracer final : public Weapon
	{
		friend class WeaponObjectPool<RuneTracer>;
		RuneTracer(Vector2 spawanPos, int damage, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<RuneTracer>* pPool);
		virtual ~RuneTracer() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void Initialize(Vector2 pos);

		__forceinline void SetDegree(float degree) { assert(std::abs(degree) >= FLT_EPSILON); mDegree = degree; }

	private:
		Image* mpRuneTracerImage;
		WeaponObjectPool<RuneTracer>* mpPool;
		int mSizeX;
		int mSizeY;
		float mDegree;
		Vector2 mRotatedVector;
		eRuneQudrant meRuneQudrant;
	};

}