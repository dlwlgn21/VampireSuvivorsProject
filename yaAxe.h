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
		Axe(Vector2 spawanPos, int damage, float speed, float knockBackValue, float shootInterval, WeaponObjectPool<Axe>* pPool);
		virtual ~Axe() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void Initialize(Vector2 pos);

	private:
		Image* mpAxeImage;
		WeaponObjectPool<Axe>* mpPool;
		int mSizeX;
		int mSizeY;
	};
}

