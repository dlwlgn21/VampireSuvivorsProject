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
	class WeaponBox;
	class PauseWeaponInfoBox;
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
		void SetPlayInfoWeaponBox(WeaponBox* pWeaponBox) { assert(pWeaponBox != nullptr); mpPlayInfoWeaponBox = pWeaponBox; };
		void SetPlayPauseWeaponBox(PauseWeaponInfoBox* pWeaponBox) { assert(pWeaponBox != nullptr); mpPauseWeaponBox = pWeaponBox; };

		Image* GetImage(const eWeaponAndItemTypes type, const UINT idx);
		Image* GetPickupedImage(const eLevelUpUI type, eWeaponAndItemTypes& out_type);
		void AddInfoIcon(const eWeaponAndItemTypes type);
		void AddLevelBoxIcon(const UINT level, const eWeaponAndItemTypes type);
		void IncreasePlayerStat(const eWeaponAndItemTypes type);
		void IncreaseWeaponIconCount(const eWeaponAndItemTypes type);
		void IncreaseBuffStatIconCount(const eWeaponAndItemTypes type);
		void IncreaseLevelBoxLevel(const std::vector<UIBase*>& child, const eWeaponAndItemTypes type);
		
	private:
		LevelUpUIManager()
			: mpPlayer(nullptr)
			, mpPlayInfoWeaponBox(nullptr)
			, mpPauseWeaponBox(nullptr)
			, mpPickupedImages{}
			, meWAndITypeMap{}
			, meWAndITypeForLevelUpHUD{}
			, mTotalActiveIconCount(1)
			, mActiveWeaponIconCount(1)
			, mActiveBuffStatIconCount(0)
		{
		}

	private:
		Player* mpPlayer;
		WeaponBox* mpPlayInfoWeaponBox;
		PauseWeaponInfoBox* mpPauseWeaponBox;
		std::vector<std::vector<Image*>> mpImages;
		Image* mpPickupedImages[static_cast<UINT>(eLevelUpUI::COUNT)];
		eWeaponAndItemTypes meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::COUNT)];
		eWeaponAndItemTypes meWAndITypeForLevelUpHUD[static_cast<UINT>(eLevelUpUI::COUNT)];

		unsigned char mTotalActiveIconCount;
		unsigned char mActiveWeaponIconCount;
		unsigned char mActiveBuffStatIconCount;

	};
}