#pragma once
#include "Common.h"

namespace ya
{
	class Image;
	class Player;
	class LevelUpUIManager final
	{
	public:
		~LevelUpUIManager() = default;
		LevelUpUIManager(const LevelUpUIManager& other) = delete;
		LevelUpUIManager& operator=(const LevelUpUIManager& other) = delete;

		static LevelUpUIManager& GetInstance();

		void Initialize();
		void ArrangeImage();
		void SetPlayer(Player* pPlayer) { assert(pPlayer != nullptr); mpPlayer = pPlayer; };

		Image* GetImage(eWeaponAndItemTypes type, UINT idx);

	private:
		LevelUpUIManager() = default;

	public:
		Player* mpPlayer;
		std::vector<std::vector<Image*>> mpImages;
	};
}