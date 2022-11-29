#pragma once
#include "yaWeapon.h"

namespace ya
{
	enum class eKnifeDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UP_LEFT,
		UP_RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT,
		COUNT
	};
	class KnifeObjectPool;
	class Image;
	class Knife final : public Weapon
	{
	public:
		Knife(Vector2 spwanPos, int damage, float speed, float knockBackValue, float shootInterval, eKnifeDirection dir, KnifeObjectPool* pPool);
		virtual ~Knife() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;
		
		void Initialize(Vector2 pos, eKnifeDirection knifeDirection);
		__forceinline eKnifeDirection GetEKnifeDirection() { return mKnifeDirection; }

	private:
		Image* mpKnifeImage;
		int mSizeX;
		int mSizeY;
		eKnifeDirection mKnifeDirection;
		KnifeObjectPool* mpKnifeObjPool;
	};

}

