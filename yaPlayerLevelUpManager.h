#pragma once
#include "Common.h"

namespace ya
{
	enum class eLevelUpUI
	{
		TOP,
		MID,
		BOT,
		COUNT
	};
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
		void PickUpImage();
		void SetPlayer(Player* pPlayer) { assert(pPlayer != nullptr); mpPlayer = pPlayer; };

		Image* GetImage(eWeaponAndItemTypes type, UINT idx);
		Image* GetPickupedImage(eLevelUpUI type);
		void IncreasePlayerStat(eWeaponAndItemTypes type);

	private:
		LevelUpUIManager() = default;

	public:
		Player* mpPlayer;
		std::vector<std::vector<Image*>> mpImages;
		Image* mpPickupedImages[static_cast<UINT>(eLevelUpUI::COUNT)];
	};
}