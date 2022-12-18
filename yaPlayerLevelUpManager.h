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
		Image* GetPickupedImage(eLevelUpUI type, eWeaponAndItemTypes& out_type);
		void IncreasePlayerStat(eWeaponAndItemTypes type);

	private:
		LevelUpUIManager()
			: mpPlayer(nullptr)
			, mpPickupedImages{}
			, meWAndITypeMap{}
			, meWAndITypeForLevelUpHUD{}
		{

		}

	public:
		Player* mpPlayer;
		std::vector<std::vector<Image*>> mpImages;
		Image* mpPickupedImages[static_cast<UINT>(eLevelUpUI::COUNT)];
		eWeaponAndItemTypes meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::COUNT)];
		eWeaponAndItemTypes meWAndITypeForLevelUpHUD[static_cast<UINT>(eLevelUpUI::COUNT)];
	};
}