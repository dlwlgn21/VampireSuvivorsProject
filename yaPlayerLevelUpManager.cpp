#include <random>
#include "yaPlayerLevelUpManager.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaWeaponBox.h"
#include "yaPlayInfoIcon.h"

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
		const int MAX_SELECTION_COUNT = 3;
		const Player::PlayerItemLevelStat& stat = mpPlayer->GetItemLevelStat();
		
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> randomDist(1, MAX_WEAPON_STAT_BURF_ITEM_COUNT - 1);
		int choice[MAX_SELECTION_COUNT] = { 0, };
		choice[0] = randomDist(gen);

		// NO DUPLICATTED CHECK Random Shuffle
		for (int i = 1; i < MAX_SELECTION_COUNT; ++i)
		{
			choice[i] = randomDist(gen);
			for (int j = 0; j < i; ++j)
			{
				if (choice[j] == choice[i])
				{
					if (choice[j] < TOTAL_WEAPON_COUNT && stat.ItemLevels[choice[j]] >= MAX_WEAPON_LEVEL ||
						choice[j] >= TOTAL_WEAPON_COUNT && stat.ItemLevels[choice[j]] >= MAX_STAT_BURF_ITEM_LEVEL)
					{
						// TODO : 이건 다시 나중에 처리하자. 예외상황이 2가지 더있어서 종합해서 처리해야 함.
						// 중복되는 번호가 나오거나, 최대 무기레벨보다 높거나, 최대 스탯버프레벨보다 높으면 다시뽑즈아.
						assert(false);
						break;
					}
					--i;    
					break;
				}
			}
		}

		// 저장해놓은 이미지 불러오기.
		for (int i = 0; i < MAX_SELECTION_COUNT; ++i)
		{
			mpPickupedImages[i] = mpImages[choice[i]][stat.ItemLevels[choice[i]]];
			meWAndITypeForLevelUpHUD[i] = meWAndITypeMap[choice[i]];
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
			}
			break;
		}
		case eWeaponAndItemTypes::FIRE_WAND:
		{
			unsigned char fireWandLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::FIRE_WAND)];
			switch (fireWandLevel)
			{
			case 0:
				IncreaseWeaponIconCount(type);
				break;
			case 1u:
				// 투사체 1개 더 발사
				break;
			case 2u:
				// 투사체 1개 더 발사
				// 기본피해 5 증가
				break;
			case 3u:
				// 투사체 1개 더 발사
				break;
			case 4u:
				// 적 1마리 추가 관통
				break;
			case 5u:
				// 적 1마리 추가 관통
				break;
			default:
				assert(false);
				break;
			}
			break;
		}
		case eWeaponAndItemTypes::RUNE:
		{
			unsigned char runeLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::RUNE)];
			switch (runeLevel)
			{
			case 0:
				IncreaseWeaponIconCount(type);
				break;
			case 1u:
				// 투사체 1개 더 발사
				break;
			case 2u:
				// 투사체 1개 더 발사
				// 기본피해 5 증가
				break;
			case 3u:
				// 투사체 1개 더 발사
				break;
			case 4u:
				// 적 1마리 추가 관통
				break;
			case 5u:
				// 적 1마리 추가 관통
				break;
			default:
				assert(false);
				break;
			}
			break;
		}
		case eWeaponAndItemTypes::AXE:
		{
			unsigned char axeLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::AXE)];
			switch (axeLevel)
			{
			case 0:
				IncreaseWeaponIconCount(type);
				break;
			case 1u:
				// 투사체 1개 더 발사
				break;
			case 2u:
				// 투사체 1개 더 발사
				// 기본피해 5 증가
				break;
			case 3u:
				// 투사체 1개 더 발사
				break;
			case 4u:
				// 적 1마리 추가 관통
				break;
			case 5u:
				// 적 1마리 추가 관통
				break;
			default:
				assert(false);
				break;
			}
			break;
		}
		case eWeaponAndItemTypes::WEAPON_SPEED:
		{
			unsigned char weaponSpeedLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)];
			if (weaponSpeedLevel == 0)
			{
				IncreaseBuffStatIconCount(type);
			}
			// 모든 무기 속도 10% 증가
			mpPlayer->IncreaseWeaponSpeedCoefficient();
			break;
		}
		case eWeaponAndItemTypes::WEAPON_DAMAGE:
		{
			unsigned char weaponDamageLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)];
			if (weaponDamageLevel == 0)
			{
				IncreaseBuffStatIconCount(type);
			}
			// 모든 무기 데미지 10% 증가
			mpPlayer->IncreaseWeaponDamageCoefficient();
			break;
		}
		case eWeaponAndItemTypes::MOVE_SPEED:
		{
			unsigned char moveSpeedLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)];
			if (moveSpeedLevel == 0)
			{
				IncreaseBuffStatIconCount(type);
			}
			// 이동속도 10% 증가
			mpPlayer->IncreaseMoveSpeed();
			break;
		}
		case eWeaponAndItemTypes::PLAYER_AMOUR:
		{
			unsigned char amourLevel = stat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)];
			if (amourLevel == 0)
			{
				IncreaseBuffStatIconCount(type);
			}
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
			float yPos = BOX_HEIGHT + Y_MARGIN_PIXEL;
			switch (mActiveBuffStatIconCount)
			{
			case 1u:
				pIcon->SetPos(Vector2(FIRST_X_POS, yPos));
				pPauseIcon->SetPos(Vector2(FIRST_X_POS + PAUSED_X_PLUS, yPos));
				break;
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
		
		Vector2 pos = pIcon->GetPos();
		float xPos = pos.x;
		float yPos = pos.y;

		Vector2 pausePos = pPauseIcon->GetPos();
		float xPausePos = pausePos.x;
		float yPausePos = pausePos.y;
		// 보정해주어야 함.
		switch (type)
		{
		case eWeaponAndItemTypes::FIRE_WAND:
		{
			pIcon->SetPos(Vector2(xPos - 2.0f, yPos - 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos - 2.0f, yPausePos - 2.0f));
			break;
		}
		case eWeaponAndItemTypes::RUNE:
		{
			pIcon->SetPos(Vector2(xPos + 3.0f, yPos + 4.0f));
			pPauseIcon->SetPos(Vector2(xPausePos + 3.0f, yPausePos + 4.0f));
			break;
		}
		case eWeaponAndItemTypes::AXE:
		{
			pIcon->SetPos(Vector2(xPos - 2.0f, yPos - 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos - 2.0f, yPausePos - 2.0f));
			break;
		}
		case eWeaponAndItemTypes::WEAPON_SPEED:
		{
			pIcon->SetPos(Vector2(xPos - 2.0f, yPos - 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos - 2.0f, yPausePos - 2.0f));
			break;
		}
		case eWeaponAndItemTypes::WEAPON_DAMAGE:
		{
			pIcon->SetPos(Vector2(xPos + 5.0f, yPos + 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos + 5.0f, yPausePos + 2.0f));
			break;
		}
		case eWeaponAndItemTypes::MOVE_SPEED:
		{
			pIcon->SetPos(Vector2(xPos, yPos));
			pPauseIcon->SetPos(Vector2(xPausePos, yPausePos));
			break;
		}
		case eWeaponAndItemTypes::PLAYER_AMOUR:
		{
			pIcon->SetPos(Vector2(xPos, yPos - 2.0f));
			pPauseIcon->SetPos(Vector2(xPausePos, yPausePos - 2.0f));
			break;
		}
		default:
			assert(false);
			break;
		}

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
}