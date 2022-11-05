#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class Backpack : public GameObject
	{
	public:
		Backpack();
		virtual ~Backpack();

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
		float mSpeed;
		Image* mpImage;
		BLENDFUNCTION mFunc;
	};
}

