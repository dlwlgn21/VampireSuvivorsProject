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
	class Image;
	class Knife final : public Weapon
	{
	public:
		Knife(Vector2 spwanPos, int damage, int count, float speed, float knockBackValue, float shootInterval, eKnifeDirection dir);
		virtual ~Knife() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
		void shoot();

	private:
		Image* mpKnifeImage;
		int mSizeX;
		int mSizeY;
		const eKnifeDirection mKnifeDirection;
		//bool mbIsLeftKeyPressed;
		//bool mbIsRightKeyPressed;
		//bool mbIsUpKeyPressed;
		//bool mbIsDownKeyPressed;
		//bool mbIsUpLeftKeyPressed;
		//bool mbIsUpRightKeyPressed;
		//bool mbIsDownLeftPressed;
		//bool mbIsDownRightPressed;
	};

}

