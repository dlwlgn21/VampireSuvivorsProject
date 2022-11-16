#pragma once
#include "yaGameObejct.h"


namespace ya
{
	class Ground final : public GameObject
	{
	public:
		Ground();
		virtual ~Ground();

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;
	private:

	};

}

