#include <random>
#include "yaPlayerLevelUpManager.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	LevelUpUIManager& LevelUpUIManager::GetInstance()
	{
		static LevelUpUIManager instance;
		return instance;
	}

	void LevelUpUIManager::Initialize()
	{
		const UINT MAX_KEY_NAME_LENGTH = 16;
		const UINT MAX_FILE_PATH_LENTH = 64;
		wchar_t keyName[MAX_KEY_NAME_LENGTH];
		wchar_t filePath[MAX_FILE_PATH_LENTH];

		mpImages.reserve(MAX_WEAPON_STAT_BURF_ITEM_COUNT);
		mpImages.resize(MAX_WEAPON_STAT_BURF_ITEM_COUNT);
		for (int i = 0; i < MAX_WEAPON_STAT_BURF_ITEM_COUNT; ++i)
		{
			if (i < TOTAL_WEAPON_COUNT)
			{ 
				mpImages[i].reserve(MAX_WEAPON_LEVEL); 
				mpImages[i].resize(MAX_WEAPON_LEVEL);
			}
			else
			{ 
				mpImages[i].reserve(MAX_STAT_BURF_ITEM_LEVEL); 
				mpImages[i].resize(MAX_STAT_BURF_ITEM_LEVEL);
			}
		}

		meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)] = eWeaponAndItemTypes::KNIFE;
		meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::FIRE_WAND)] = eWeaponAndItemTypes::FIRE_WAND;
		meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::RUNE)] = eWeaponAndItemTypes::RUNE;
		meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::AXE)] = eWeaponAndItemTypes::AXE;
		meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)] = eWeaponAndItemTypes::WEAPON_SPEED;
		meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)] = eWeaponAndItemTypes::WEAPON_DAMAGE;
		meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)] = eWeaponAndItemTypes::MOVE_SPEED;
		meWAndITypeMap[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)] = eWeaponAndItemTypes::PLAYER_AMOUR;

		for (int i = 1; i < MAX_WEAPON_LEVEL; ++i)
		{
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"KnifeLevel%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\KnifeLevel%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)][i] != nullptr);
		}


		// FOR TEST
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::FIRE_WAND)][0] = Resources::Load<Image>(L"FireWand2", L"Resources\\Image\\LevelUpImage\\FireWand2.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::FIRE_WAND)][0] != nullptr);
		for (int i = 1; i < MAX_WEAPON_LEVEL; ++i)
		{
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::FIRE_WAND)][i] = mpImages[static_cast<UINT>(eWeaponAndItemTypes::FIRE_WAND)][0];
		}

		// FOR TEST
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::AXE)][0] = Resources::Load<Image>(L"FireWand3", L"Resources\\Image\\LevelUpImage\\FireWand3.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::AXE)][0] != nullptr);
		for (int i = 1; i < MAX_WEAPON_LEVEL; ++i)
		{
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::AXE)][i] = mpImages[static_cast<UINT>(eWeaponAndItemTypes::AXE)][0];
		}

		// FOR TEST
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::RUNE)][0] = Resources::Load<Image>(L"FireWand4", L"Resources\\Image\\LevelUpImage\\FireWand4.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::RUNE)][0] != nullptr);
		for (int i = 1; i < MAX_WEAPON_LEVEL; ++i)
		{
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::RUNE)][i] = mpImages[static_cast<UINT>(eWeaponAndItemTypes::RUNE)][0];
		}

		// FOR TEST
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][0] = Resources::Load<Image>(L"WeaponSpeed1", L"Resources\\Image\\LevelUpImage\\WeaponSpeed1.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][0] != nullptr);
		for (int i = 1; i < MAX_STAT_BURF_ITEM_LEVEL; ++i)
		{
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][i] = mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][0];
		}

		// FOR TEST
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)][0] = Resources::Load<Image>(L"WeaponDamage1", L"Resources\\Image\\LevelUpImage\\WeaponDamage1.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)][0] != nullptr);
		for (int i = 1; i < MAX_STAT_BURF_ITEM_LEVEL; ++i)
		{
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)][i] = mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)][0];
		}

		// FOR TEST
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)][0] = Resources::Load<Image>(L"MoveSpeed1", L"Resources\\Image\\LevelUpImage\\MoveSpeed1.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)][0] != nullptr);
		for (int i = 1; i < MAX_STAT_BURF_ITEM_LEVEL; ++i)
		{
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)][i] = mpImages[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)][0];
		}

		// FOR TEST
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)][0] = Resources::Load<Image>(L"Amour1", L"Resources\\Image\\LevelUpImage\\Amour1.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)][0] != nullptr);
		for (int i = 1; i < MAX_STAT_BURF_ITEM_LEVEL; ++i)
		{
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)][i] = mpImages[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)][0];
		}

	}

	void LevelUpUIManager::PickUpImage()
	{
		// TODO : LevelUP에 따른 이미지 뽑기 구현해야함.
		assert(mpPlayer != nullptr);
		const int MAX_SELECTION_COUNT = 3;
		const Player::PlayerItemLevelStat& stat = mpPlayer->GetItemLevelStat();
		
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> randomDist(1, MAX_WEAPON_STAT_BURF_ITEM_COUNT);
		int choice[MAX_SELECTION_COUNT] = { 0, };
		choice[0] = randomDist(gen);

		// NO DUPLICATTED CHECK Random Shuffle
		for (int i = 1; i < MAX_SELECTION_COUNT; ++i)
		{
			choice[i] = randomDist(gen);
			if (choice[i] == choice[i - 1] || 
				choice[i] <= TOTAL_WEAPON_COUNT && stat.ItemLevels[choice[i]] >= MAX_WEAPON_LEVEL ||
				choice[i] > TOTAL_WEAPON_COUNT && stat.ItemLevels[choice[i]] >= MAX_STAT_BURF_ITEM_LEVEL)
			{
				// 중복되는 번호가 나오거나, 최대 무기레벨보다 높거나, 최대 스탯버프레벨보다 높으면 다시뽑즈아.
				--i;
				continue;
			}
		}

		// 저장해놓은 이미지 불러오기.
		for (int i = 0; i < MAX_SELECTION_COUNT; ++i)
		{
			mpPickupedImages[i] = mpImages[choice[i]][stat.ItemLevels[choice[i]]];
			meWAndITypeForLevelUpHUD[i] = meWAndITypeMap[choice[i]];
		}
	}
	Image* LevelUpUIManager::GetImage(eWeaponAndItemTypes type, UINT idx)
	{
		assert(mpImages[static_cast<UINT>(type)][idx] != nullptr);
		return mpImages[static_cast<UINT>(type)][idx];
	}

	Image* LevelUpUIManager::GetPickupedImage(eLevelUpUI type, eWeaponAndItemTypes& out_type)
	{
		assert(mpPickupedImages[static_cast<UINT>(type)] != nullptr);
		out_type = meWAndITypeForLevelUpHUD[static_cast<UINT>(type)];
		return mpPickupedImages[static_cast<UINT>(type)];
	}
	void LevelUpUIManager::IncreasePlayerStat(eWeaponAndItemTypes type)
	{
		assert(mpPlayer != nullptr);
		const Player::PlayerItemLevelStat& stat = mpPlayer->GetItemLevelStat();
		switch (type)
		{
		case eWeaponAndItemTypes::KNIFE:
		{
			unsigned char knifeLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)];
			switch (knifeLevel)
			{
			case 2u:
				// 투사체 1개 더 발사
				break;
			case 3u:
				// 투사체 1개 더 발사
				// 기본피해 5 증가
				break;
			case 4u:
				// 투사체 1개 더 발사
				break;
			case 5u:
				// 적 1마리 추가 관통
				break;
			case 6u:
				// 투사체 1개 더 발사
				break;
			case 7u:
				// 투사체 1개 더 발사
				// 기본피해 5 증가
				break;
			case 8:
				// 적 1마리 추가 관통
				break;
			default:
				assert(false);
				break;
			}
			break;
		}
		case eWeaponAndItemTypes::FIRE_WAND:
		{

			break;
		}
		case eWeaponAndItemTypes::RUNE:
		{

			break;
		}
		case eWeaponAndItemTypes::AXE:
		{

			break;
		}
		case eWeaponAndItemTypes::WEAPON_SPEED:
		{
			// 모든 무기 속도 10% 증가
			mpPlayer->IncreaseWeaponSpeedCoefficient();
			break;
		}
		case eWeaponAndItemTypes::WEAPON_DAMAGE:
		{
			// 모든 무기 데미지 10% 증가
			mpPlayer->IncreaseWeaponDamageCoefficient();
			break;
		}
		case eWeaponAndItemTypes::MOVE_SPEED:
		{
			// 이동속도 10% 증가
			mpPlayer->IncreaseMoveSpeed();
			break;
		}
		case eWeaponAndItemTypes::PLAYER_AMOUR:
		{
			// 받는피해 1 감소
			mpPlayer->IncreaseAmour();
			break;
		}
		default:
			assert(false);
			break;
		}

	}
}