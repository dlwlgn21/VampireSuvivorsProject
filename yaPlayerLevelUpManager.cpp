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

		for (int i = 1; i < MAX_WEAPON_LEVEL; ++i)
		{
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"KnifeLevel%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\KnifeLevel%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)][i] != nullptr);
		}

		mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][0] = Resources::Load<Image>(L"WeaponSpeed1", L"Resources\\Image\\LevelUpImage\\WeaponSpeed1.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][0] != nullptr);
		
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)][0] = Resources::Load<Image>(L"WeaponDamage1", L"Resources\\Image\\LevelUpImage\\WeaponDamage1.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)][0] != nullptr);
		
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)][0] = Resources::Load<Image>(L"MoveSpeed1", L"Resources\\Image\\LevelUpImage\\MoveSpeed1.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)][0] != nullptr);
		
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)][0] = Resources::Load<Image>(L"Amour1", L"Resources\\Image\\LevelUpImage\\Amour1.bmp");
		assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)][0] != nullptr);

	}

	void LevelUpUIManager::ArrangeImage()
	{
		//// TODO : LevelUP�� ���� �̹��� �̱� �����ؾ���.
		//assert(mpPlayer != nullptr);
		//const int MAX_SELECTION_COUNT = 3;
		//const Player::PlayerItemLevelStat& stat = mpPlayer->GetItemStat();
		//
		//std::random_device rd;
		//std::mt19937 gen(rd());
		//std::uniform_int_distribution<> weponDist(1, TOTAL_WEAPON_COUNT);
		//std::uniform_int_distribution<> randomDist(1, MAX_WEAPON_STAT_BURF_ITEM_COUNT);
		//int choice[MAX_SELECTION_COUNT] = { 0, };
		//choice[0] = weponDist(gen);

		//// NO DUPLICATTED CHECK Random Shuffle
		//for (int i = 1; i < MAX_SELECTION_COUNT; ++i)
		//{
		//	choice[i] = randomDist(gen);
		//	if (choice[i] == choice[i - 1] || 
		//		choice[i] <= TOTAL_WEAPON_COUNT && stat.ItemLevels[choice[i]] >= MAX_WEAPON_LEVEL ||
		//		choice[i] > TOTAL_WEAPON_COUNT && stat.ItemLevels[choice[i]] >= MAX_STAT_BURF_ITEM_LEVEL)
		//	{
		//		// �ߺ��Ǵ� ��ȣ�� �����ų�, �ִ� ���ⷹ������ ���ų�, �ִ� ���ȹ����������� ������ �ٽû����.
		//		--i;
		//		continue;
		//	}
		//}

		//// �����س��� �̹��� �ҷ�����.
		//for (int i = 0; i < MAX_SELECTION_COUNT; ++i)
		//{

		//}

	}
	Image* LevelUpUIManager::GetImage(eWeaponAndItemTypes type, UINT idx)
	{
		assert(mpImages[static_cast<UINT>(type)][idx] != nullptr);
		return mpImages[static_cast<UINT>(type)][idx];
	}
}