#pragma once
#include "yaWeapon.h"

namespace ya
{
	class Image;
	template<typename T> class WeaponObjectPool;
	class FireWand final : public Weapon
	{
	public:
		friend class WeaponObjectPool<FireWand>;
		FireWand(Vector2 spawanPos, int damage, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<FireWand>* pPool);
		virtual ~FireWand() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;
		__forceinline void SetIdx(UINT idx) { mIdx = idx; }
		void Initialize(Vector2 pos);

	private:
		void initAndSetVelocity();

	private:
		Image* mpFireImage;
		WeaponObjectPool<FireWand>* mpPool;
		int mSizeX;
		int mSizeY;
		float mVelocityX;
		float mVelocityY;
		UINT mIdx;
	};
}

