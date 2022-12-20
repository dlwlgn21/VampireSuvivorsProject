#include <random>
#include "yaPlayerLevelUpManager.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaWeaponBox.h"
#include "yaPlayInfoIcon.h"
#include "yaPauseWeaponInfoBox.h"
#include "yaLevelBoxIcon.h"

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
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"KnifeL%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\KnifeLevel%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)][i] != nullptr);
		}

		for (int i = 0; i < MAX_WEAPON_LEVEL; ++i)
		{
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"FireWand%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\FireWand%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::FIRE_WAND)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::FIRE_WAND)][i] != nullptr);
		}

		for (int i = 0; i < MAX_WEAPON_LEVEL; ++i)
		{
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"Axe%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\Axe%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::AXE)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::AXE)][i] != nullptr);
		}

		for (int i = 0; i < MAX_WEAPON_LEVEL; ++i)
		{
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"Rune%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\Rune%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::RUNE)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::RUNE)][i] != nullptr);
		}

		for (int i = 0; i < 3; ++i)
		{
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"WeaponSpeed%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\WeaponSpeed%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][i] != nullptr);
		}
		// TODO: 레벨 4 이미지 추출해야함.
		mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][3] = mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)][2];


		for (int i = 0; i < MAX_STAT_BURF_ITEM_LEVEL; ++i)
		{
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"WeaponDamage%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\WeaponDamage%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)][i] != nullptr);
		}

		for (int i = 0; i < MAX_STAT_BURF_ITEM_LEVEL; ++i)
		{
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"MoveSpeed%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\MoveSpeed%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)][i] != nullptr);
		}

		for (int i = 0; i < MAX_STAT_BURF_ITEM_LEVEL; ++i)
		{
			swprintf_s(keyName, MAX_KEY_NAME_LENGTH, L"Amour%d", i + 1);
			swprintf_s(filePath, MAX_FILE_PATH_LENTH, L"Resources\\Image\\LevelUpImage\\Amour%d.bmp", i + 1);
			mpImages[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)][i] = Resources::Load<Image>(keyName, filePath);
			assert(mpImages[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)][i] != nullptr);
		}
	}

	void LevelUpUIManager::PickUpImage()
	{
		// TODO : LevelUP에 따른 이미지 뽑기 구현해야함.
		assert(mpPlayer != nullptr);
		const unsigned char MAX_SELECTION_COUNT = 3;
		const unsigned char THREE_IMAGE_CAN_DISPLAY_COUNT = 5;
		const Player::PlayerItemLevelStat& stat = mpPlayer->GetItemLevelStat();
		
		bool isThreeImageDisplay = false;
		bool isTwoImageDisplay = false;
		bool isOneImageDisplay = false;


		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> randomDist(0, MAX_WEAPON_STAT_BURF_ITEM_COUNT - 1);

		unsigned char imageCountOnUI = 0;
		unsigned char maxLevelCount = 0;
		bool isReachMaxLevels[MAX_WEAPON_STAT_BURF_ITEM_COUNT] = { false, };
		unsigned char level;

		// How Many Image On UI
		for (int i = 0; i < MAX_WEAPON_STAT_BURF_ITEM_COUNT; ++i)
		{
			level = stat.ItemLevels[i];
			if (i < TOTAL_WEAPON_COUNT)
			{
				if (level >= MAX_WEAPON_LEVEL)
				{
					isReachMaxLevels[i] = true;
					++maxLevelCount;
				}
			}
			else
			{
				if (level >= MAX_STAT_BURF_ITEM_LEVEL)
				{
					isReachMaxLevels[i] = true;
					++maxLevelCount;
				}
			}
		}

		unsigned char threeChoice[MAX_SELECTION_COUNT] = { 0, };
		threeChoice[0] = randomDist(gen);

		unsigned char twoChoice[2];
		unsigned char twoChoiceIdx = 0;
		unsigned char oneChoice;

		// NO DUPLICATTED CHECK Random Shuffle
		if (maxLevelCount <= THREE_IMAGE_CAN_DISPLAY_COUNT)
		{
			isThreeImageDisplay = true;
			for (int i = 1; i < MAX_SELECTION_COUNT; ++i)
			{
				threeChoice[i] = randomDist(gen);
				for (int j = 0; j < i; ++j)
				{
					if (threeChoice[j] == threeChoice[i] || isReachMaxLevels[j])
					{ 
						--i; 
						break; 
					}
				}
			}
		}
		else if (maxLevelCount == THREE_IMAGE_CAN_DISPLAY_COUNT + 1)
		{
			isTwoImageDisplay = true;
			for (int i = 0; i < MAX_WEAPON_STAT_BURF_ITEM_COUNT; ++i)
			{
				if (!isReachMaxLevels[i])
					{ twoChoice[twoChoiceIdx++] = i; }
			}
		}
		else if (maxLevelCount == THREE_IMAGE_CAN_DISPLAY_COUNT + 2)
		{
			isOneImageDisplay = true;
			for (int i = 0; i < MAX_WEAPON_STAT_BURF_ITEM_COUNT; ++i)
			{
				if (!isReachMaxLevels[i])
				{
					oneChoice = i;
					break;
				}
			}
		}
		else
		{
			// 모든 아이템 최종 레벨 도달.
			assert(false);
		}

		// 저장해놓은 이미지 불러오기.
		if (isThreeImageDisplay)
		{
			for (int i = 0; i < MAX_SELECTION_COUNT; ++i)
			{
				mpPickupedImages[i] = mpImages[threeChoice[i]][stat.ItemLevels[threeChoice[i]]];
				meWAndITypeForLevelUpHUD[i] = meWAndITypeMap[threeChoice[i]];
			}
			return;
		}

		if (isTwoImageDisplay)
		{
			for (int i = 0; i < MAX_SELECTION_COUNT - 1; ++i)
			{
				mpPickupedImages[i] = mpImages[twoChoice[i]][stat.ItemLevels[twoChoice[i]]];
				meWAndITypeForLevelUpHUD[i] = meWAndITypeMap[twoChoice[i]];
			}
			return;
		}

		if (isOneImageDisplay)
		{
			mpPickupedImages[0] = mpImages[oneChoice][stat.ItemLevels[oneChoice]];
			meWAndITypeForLevelUpHUD[0] = meWAndITypeMap[oneChoice];
			return;
		}
	}
	Image* LevelUpUIManager::GetImage(const eWeaponAndItemTypes type, const UINT idx)
	{
		assert(mpImages[static_cast<UINT>(type)][idx] != nullptr);
		return mpImages[static_cast<UINT>(type)][idx];
	}

	Image* LevelUpUIManager::GetPickupedImage(const eLevelUpUI type, eWeaponAndItemTypes& out_type)
	{
		assert(mpPickupedImages[static_cast<UINT>(type)] != nullptr);
		out_type = meWAndITypeForLevelUpHUD[static_cast<UINT>(type)];
		return mpPickupedImages[static_cast<UINT>(type)];
	}
	void LevelUpUIManager::IncreasePlayerStat(const eWeaponAndItemTypes type)
	{
		assert(mpPlayer != nullptr);
		const Player::PlayerItemLevelStat& stat = mpPlayer->GetItemLevelStat();
		const std::vector<UIBase*>& pauseWeaponBoxChild = mpPauseWeaponBox->GetChild();
		switch (type)
		{
		case eWeaponAndItemTypes::KNIFE:
		{
			unsigned char knifeLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)];
			assert(knifeLevel <= MAX_WEAPON_LEVEL);

			IncreaseLevelBoxLevel(pauseWeaponBoxChild, eWeaponAndItemTypes::KNIFE);
			mpPlayer->IncreaseWeaponLevel(eWeaponAndItemTypes::KNIFE);
			mpPlayer->IncreaseWeaponStat(eWeaponAndItemTypes::KNIFE);
			break;
		}
		case eWeaponAndItemTypes::FIRE_WAND:
		{
			unsigned char fireWandLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::FIRE_WAND)];
			assert(fireWandLevel <= MAX_WEAPON_LEVEL);

			if (fireWandLevel == 0)
				{ IncreaseWeaponIconCount(type); }
			else
				{ IncreaseLevelBoxLevel(pauseWeaponBoxChild, eWeaponAndItemTypes::FIRE_WAND); }
			mpPlayer->IncreaseWeaponLevel(eWeaponAndItemTypes::FIRE_WAND);
			mpPlayer->IncreaseWeaponStat(eWeaponAndItemTypes::FIRE_WAND);
			break;
		}
		case eWeaponAndItemTypes::RUNE:
		{
			unsigned char runeLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::RUNE)];
			assert(runeLevel <= MAX_WEAPON_LEVEL);

			if (runeLevel == 0)
				{ IncreaseWeaponIconCount(type); }
			else
				{ IncreaseLevelBoxLevel(pauseWeaponBoxChild, eWeaponAndItemTypes::RUNE); }
			mpPlayer->IncreaseWeaponLevel(eWeaponAndItemTypes::RUNE);
			mpPlayer->IncreaseWeaponStat(eWeaponAndItemTypes::RUNE);
			break;
		}
		case eWeaponAndItemTypes::AXE:
		{
			unsigned char axeLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::AXE)];
			assert(axeLevel <= MAX_WEAPON_LEVEL);

			if (axeLevel == 0)
				{ IncreaseWeaponIconCount(type); }
			else
				{ IncreaseLevelBoxLevel(pauseWeaponBoxChild, eWeaponAndItemTypes::AXE); }
			mpPlayer->IncreaseWeaponLevel(eWeaponAndItemTypes::AXE);
			mpPlayer->IncreaseWeaponStat(eWeaponAndItemTypes::AXE);
			break;
		}
		case eWeaponAndItemTypes::WEAPON_SPEED:
		{
			unsigned char weaponSpeedLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)];
			if (weaponSpeedLevel == 0)
				{ IncreaseBuffStatIconCount(type); }
			else
				{ IncreaseLevelBoxLevel(pauseWeaponBoxChild, eWeaponAndItemTypes::WEAPON_SPEED); }
			// 모든 무기 속도 10% 증가
			mpPlayer->IncreaseWeaponSpeedCoefficient();
			break;
		}
		case eWeaponAndItemTypes::WEAPON_DAMAGE:
		{
			unsigned char weaponDamageLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)];
			if (weaponDamageLevel == 0)
				{ IncreaseBuffStatIconCount(type); }
			else
				{ IncreaseLevelBoxLevel(pauseWeaponBoxChild, eWeaponAndItemTypes::WEAPON_DAMAGE); }
			// 모든 무기 데미지 10% 증가
			mpPlayer->IncreaseWeaponDamageCoefficient();
			break;
		}
		case eWeaponAndItemTypes::MOVE_SPEED:
		{
			unsigned char moveSpeedLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)];
			if (moveSpeedLevel == 0)
				{ IncreaseBuffStatIconCount(type); }
			else
				{ IncreaseLevelBoxLevel(pauseWeaponBoxChild, eWeaponAndItemTypes::MOVE_SPEED); }
			// 이동속도 10% 증가
			mpPlayer->IncreaseMoveSpeed();
			break;
		}
		case eWeaponAndItemTypes::PLAYER_AMOUR:
		{
			unsigned char amourLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)];
			if (amourLevel == 0)
				{ IncreaseBuffStatIconCount(type); }
			else
				{ IncreaseLevelBoxLevel(pauseWeaponBoxChild, eWeaponAndItemTypes::PLAYER_AMOUR); }
			// 받는피해 1 감소
			mpPlayer->IncreaseAmour();
			break;
		}
		default:
			assert(false);
			break;
		}

	}
	void LevelUpUIManager::AddInfoIcon(const eWeaponAndItemTypes type)
	{
		assert(mpPlayInfoWeaponBox != nullptr);
		assert(mpPauseWeaponBox != nullptr);
		const float X_MARGIN_PIXEL = 5.0f;
		const float Y_MARGIN_PIXEL = 5.0f;
		const float BOX_WIDTH = 33.0f;
		const float BOX_HEIGHT = 33.0f;

		const float FIRST_X_POS = 0.f;
		const float SECOND_X_POS = BOX_WIDTH + X_MARGIN_PIXEL;
		const float THIRD_X_POS = BOX_WIDTH * 2 + X_MARGIN_PIXEL * 2;
		const float FOUTH_X_POS = BOX_WIDTH * 3 + X_MARGIN_PIXEL * 3;

		const float PAUSED_X_PLUS = 95.0f;
		PlayInfoIcon* pIcon = new PlayInfoIcon(eUIType::PLAY_INFO_HUD,ePlayInfoIconPos::TOP, type, Vector2::ZERO);
		PlayInfoIcon* pPauseIcon = new PlayInfoIcon(eUIType::PLAY_PAUSED, ePlayInfoIconPos::TOP, type, Vector2::ZERO);
		mpPlayInfoWeaponBox->AddUIChild(pIcon);
		mpPauseWeaponBox->AddUIChild(pPauseIcon);
		LevelBoxIcon* pLevelBoxIcon = new LevelBoxIcon();
		pPauseIcon->AddUIChild(pLevelBoxIcon);
		pLevelBoxIcon->SetType(type);
		if (static_cast<UINT>(type) <= static_cast<UINT>(eWeaponAndItemTypes::AXE))
		{
			float yPos = 0.f;
			switch (mActiveWeaponIconCount)
			{
			case 2u:
				pIcon->SetPos(Vector2(SECOND_X_POS, yPos));
				pPauseIcon->SetPos(Vector2(SECOND_X_POS + PAUSED_X_PLUS, yPos));
				break;
			case 3u:
				pIcon->SetPos(Vector2(THIRD_X_POS, yPos));
				pPauseIcon->SetPos(Vector2(THIRD_X_POS + PAUSED_X_PLUS, yPos));
				break;
			case 4u:
				pIcon->SetPos(Vector2(FOUTH_X_POS, yPos));
				pPauseIcon->SetPos(Vector2(FOUTH_X_POS + PAUSED_X_PLUS, yPos));
				break;
			default:
				assert(false);
				break;
			}
		}
		else
		{
			const float Y_POS = BOX_HEIGHT + Y_MARGIN_PIXEL;
			const float Y_PAUSE_CORRECTION_VALUE = 20.0f;
			switch (mActiveBuffStatIconCount)
			{
			case 1u:
				pIcon->SetPos(Vector2(FIRST_X_POS, Y_POS));
				pPauseIcon->SetPos(Vector2(FIRST_X_POS + PAUSED_X_PLUS, Y_POS + Y_PAUSE_CORRECTION_VALUE));
				break;
			case 2u:
				pIcon->SetPos(Vector2(SECOND_X_POS, Y_POS));
				pPauseIcon->SetPos(Vector2(SECOND_X_POS + PAUSED_X_PLUS, Y_POS + Y_PAUSE_CORRECTION_VALUE));
				break;
			case 3u:
				pIcon->SetPos(Vector2(THIRD_X_POS, Y_POS));
				pPauseIcon->SetPos(Vector2(THIRD_X_POS + PAUSED_X_PLUS, Y_POS + Y_PAUSE_CORRECTION_VALUE));
				break;
			case 4u:
				pIcon->SetPos(Vector2(FOUTH_X_POS, Y_POS));
				pPauseIcon->SetPos(Vector2(FOUTH_X_POS + PAUSED_X_PLUS, Y_POS + Y_PAUSE_CORRECTION_VALUE));
				break;
			default:
				assert(false);
				break;
			}
		}
		
		Vector2 pos = pIcon->GetPos();
		float xPos = pos.x;
		float yPos = pos.y;

		Vector2 pausePos = pPauseIcon->GetPos();
		float xPausePos = pausePos.x;
		float yPausePos = pausePos.y;
		// 보정해주어야 함.
		const float WEAPON_X_PLUS_VALUE = 43.0f;
		const float WEAPON_Y_PLUS_VALUE = 14.0f;		
		
		const float BUFF_STAT_X_PLUS_VALUE = 42.0f;
		const float BUFF_STAT_Y_PLUS_VALUE = 12.0f;
		switch (type)
		{
		case eWeaponAndItemTypes::FIRE_WAND:
		{
			pIcon->SetPos(Vector2(xPos - 2.0f, yPos - 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos - 2.0f, yPausePos - 2.0f));
			pLevelBoxIcon->SetPos(Vector2(102.0f + WEAPON_X_PLUS_VALUE, 99.0f + WEAPON_Y_PLUS_VALUE));

			break;
		}
		case eWeaponAndItemTypes::RUNE:
		{
			pIcon->SetPos(Vector2(xPos + 3.0f, yPos + 4.0f));
			pPauseIcon->SetPos(Vector2(xPausePos + 3.0f, yPausePos + 4.0f));
			pLevelBoxIcon->SetPos(Vector2(102.0f + WEAPON_X_PLUS_VALUE, 93.0f + WEAPON_Y_PLUS_VALUE));

			break;
		}
		case eWeaponAndItemTypes::AXE:
		{
			pIcon->SetPos(Vector2(xPos - 2.0f, yPos - 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos - 2.0f, yPausePos - 2.0f));
			pLevelBoxIcon->SetPos(Vector2(102.0f + WEAPON_X_PLUS_VALUE, 99.0f + WEAPON_Y_PLUS_VALUE));
			break;
		}
		case eWeaponAndItemTypes::WEAPON_SPEED:
		{
			pIcon->SetPos(Vector2(xPos - 2.0f, yPos - 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos - 2.0f, yPausePos - 2.0f));
			pLevelBoxIcon->SetPos(Vector2(104.0f + BUFF_STAT_X_PLUS_VALUE, 105.0f + BUFF_STAT_Y_PLUS_VALUE));
			break;
		}
		case eWeaponAndItemTypes::WEAPON_DAMAGE:
		{
			pIcon->SetPos(Vector2(xPos + 5.0f, yPos + 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos + 5.0f, yPausePos + 2.0f));
			pLevelBoxIcon->SetPos(Vector2(97.0f + BUFF_STAT_X_PLUS_VALUE, 101.0f + BUFF_STAT_Y_PLUS_VALUE));
			break;
		}
		case eWeaponAndItemTypes::MOVE_SPEED:
		{
			pIcon->SetPos(Vector2(xPos, yPos));
			pPauseIcon->SetPos(Vector2(xPausePos, yPausePos));
			pLevelBoxIcon->SetPos(Vector2(100.0f + BUFF_STAT_X_PLUS_VALUE, 103.0f + BUFF_STAT_Y_PLUS_VALUE));
			break;
		}
		case eWeaponAndItemTypes::PLAYER_AMOUR:
		{
			pIcon->SetPos(Vector2(xPos, yPos - 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos, yPausePos - 2.0f));
			pLevelBoxIcon->SetPos(Vector2(101.0f + BUFF_STAT_X_PLUS_VALUE, 105.0f + BUFF_STAT_Y_PLUS_VALUE));
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void LevelUpUIManager::AddLevelBoxIcon(const UINT level, const eWeaponAndItemTypes type)
	{
	}
	void LevelUpUIManager::IncreaseWeaponIconCount(const eWeaponAndItemTypes type)
	{
		++mActiveWeaponIconCount;
		++mTotalActiveIconCount;
		assert(mActiveWeaponIconCount <= TOTAL_WEAPON_COUNT && mTotalActiveIconCount <= TOTAL_WEAPON_COUNT + TOTAL_WEAPON_COUNT);
		AddInfoIcon(type);
	}
	void LevelUpUIManager::IncreaseBuffStatIconCount(const eWeaponAndItemTypes type)
	{
		++mActiveBuffStatIconCount;
		++mTotalActiveIconCount;
		assert(mActiveBuffStatIconCount <= TOTAL_STAT_BURF_ITEM_COUNT && mTotalActiveIconCount <= TOTAL_WEAPON_COUNT + TOTAL_WEAPON_COUNT);
		AddInfoIcon(type);
	}

	void LevelUpUIManager::IncreaseLevelBoxLevel(const std::vector<UIBase*>& child, const eWeaponAndItemTypes type)
	{
		for (auto* e : child)
		{
			if (static_cast<PlayInfoIcon*>(e)->GetType() == type)
			{
				const std::vector<UIBase*>& childOfChild = static_cast<PlayInfoIcon*>(e)->GetChild();
				static_cast<LevelBoxIcon*>(childOfChild[0])->IncreaseLevel();
				return;
			}
		}
		assert(false);
	}
}