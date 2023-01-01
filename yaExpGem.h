#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class Player;
	class Collider;
	class ExpGem final : public GameObject
	{
	public:
		ExpGem(Vector2 pos, Player* pPlayer, int exp);
		virtual ~ExpGem() = default;

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* pCollider) override;
		void OnCollisionStay(Collider* pCollider) override;
		void OnCollisionExit(Collider* pCollider) override;

	private:
		Image* mpImage;
		Player* mpPlayer;
		Collider* mpCollider;
		int mImgWidth;
		int mImgHeight;
		int mExp;
		BLENDFUNCTION mBlendFunc;
	};

}

