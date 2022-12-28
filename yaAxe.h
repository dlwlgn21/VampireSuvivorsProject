#pragma once
#include "yaWeapon.h"

namespace ya
{
	class Image;
	template<typename T> class WeaponObjectPool;
	class Axe final : public Weapon 
	{
	public:
		friend class WeaponObjectPool<Axe>;
		Axe(Vector2 spawanPos, int damage, int penetratingCount, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<Axe>* pPool);
		virtual ~Axe() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void Initialize(Vector2 pos);

	private:
		void initPosAndAccel();
	private:
		Image* mpAxeImage;
		WeaponObjectPool<Axe>* mpPool;
		int mSizeX;
		int mSizeY;
		const float M_INITIAL_SPEED;
		float mVelocityX;
		float mVelocityY;
		float mAccel;
	};
}

