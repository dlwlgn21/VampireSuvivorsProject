#pragma once
#include "yaGameObejct.h"
namespace ya
{
	class Image;
	class Animator;
	class Missile : public GameObject
	{
	public:
		Missile();
		virtual ~Missile();

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
		float mSpeed;
		float mLifeTime;
		Image* mpImage;
		Animator* mpAnimator;
	public:
		Vector2 mDir;
		Vector2 mDestPos;
	};

};

