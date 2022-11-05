#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class Monster : public GameObject
	{
	public:
		Monster();
		Monster(Vector2 pos);
		virtual ~Monster();

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
		HPEN mPen;
		HBRUSH mBrush;
		Image* mpImage;
	};

}

