#include "yaMonsterFactory.h"
#include "yaMonster.h"
#include "yaMudman.h"
#include "yaPlayer.h"
#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaObjectPool.h"
#include "yaExpGemObjPool.h"
#include "yaMonsterObjPool.h"
#include "yaGreenGhost.h"


namespace ya
{
	Monster* MonsterFactory::CreateMonster(eMonsterType eType, Vector2 pos, Player* pPlayer, ExpGemObjPool* pExpGemObejctPool, MonsterObjPool<Monster>* pMonsterObjPool)
	{
		assert(pExpGemObejctPool != nullptr);
		assert(pMonsterObjPool != nullptr);

		Monster* pMonster = nullptr;
		switch (eType)
		{
		case eMonsterType::MUDMAN:
		{
			MonsterCreateInfo info(
				pos,
				pPlayer,
				MUDMAN_INITIAL_HP, 
				MUDMAN_INITIAL_DAMAGE, 
				ONE_MIN_NORMAL_MONSTER_EXP, 
				200.0f,
				Vector2(56.0f, 66.0f),
				Vector2(56.0f, 56.0f),
				Vector2::ZERO,
				5,
				7,
				0.15f,
				0.15f * 7
			);
			pMonster = pMonsterObjPool->Get(
				eMonsterType::MUDMAN,
				info,
				L"MudmanRMove",
				L"MudmanLMove",
				L"MudmanRDeath",
				L"MudmanLDeath",
				L"Resources\\Image\\MudmanRAnim.bmp",
				L"Resources\\Image\\MudmanLAnim.bmp",
				L"Resources\\Image\\MudManDeathRightAnim.bmp",
				L"Resources\\Image\\MudManLeftDeathAnim.bmp",
				pExpGemObejctPool,
				pMonsterObjPool
			);
			Scene* scene = SceneManager::GetSpecifiedScene(eSceneType::PLAY_SCENE);
			scene->AddGameObject(static_cast<GameObject*>(pMonster), eColliderLayer::MONSTER);
			return pMonster;
			break;
		}
		case eMonsterType::GREEN_GHOST:
		{
			MonsterCreateInfo info(
				pos,
				pPlayer,
				GREEN_GHOST_INITIAL_HP,
				GREEN_GHOST_INITIAL_DAMAGE,
				ONE_MIN_NORMAL_MONSTER_EXP,
				160.0f,
				Vector2(36.0f, 62.0f),
				Vector2(70.0f, 78.0f),
				Vector2::ZERO,
				4,
				6,
				0.15f,
				0.15f * 6
			);
			pMonster = pMonsterObjPool->Get(
				eMonsterType::GREEN_GHOST,
				info,
				L"GreenGhostRMove",
				L"GreenGhostLMove",
				L"GreenGhostRDeath",
				L"GreenGhostLDeath",
				L"Resources\\Image\\GreenGhostRightAnim.bmp",
				L"Resources\\Image\\GreenGhostLeftAnim.bmp",
				L"Resources\\Image\\GreenGhostRightDeathAnim.bmp",
				L"Resources\\Image\\GreenGhostLeftDeathAnim.bmp",
				pExpGemObejctPool,
				pMonsterObjPool
			);
			Scene* scene = SceneManager::GetSpecifiedScene(eSceneType::PLAY_SCENE);
			scene->AddGameObject(static_cast<GameObject*>(pMonster), eColliderLayer::MONSTER);
			return pMonster;
			break;
		}
		case eMonsterType::MEDUSA_HEAD:
		{
			MonsterCreateInfo info(
				pos,
				pPlayer,
				MEDUSA_HEAD_INITIAL_HP,
				MEDUSA_HEAD_INITIAL_DAMAGE,
				ONE_MIN_NORMAL_MONSTER_EXP,
				240.0f,
				Vector2(48.0f, 56.0f),
				Vector2(50.0f, 68.0f),
				Vector2::ZERO,
				5,
				8,
				0.15f,
				0.15f * 8
			);
			pMonster = pMonsterObjPool->Get(
				eMonsterType::GREEN_GHOST,
				info,
				L"MedusaHeadRMove",
				L"MedusaHeadLMove",
				L"MedusaHeadRDeath",
				L"MedusaHeadLDeath",
				L"Resources\\Image\\MedusaHeadRightAnim.bmp",
				L"Resources\\Image\\MedusaHeadLeftAnim.bmp",
				L"Resources\\Image\\MedusaHeadRightDeathAnim.bmp",
				L"Resources\\Image\\MedusaHeadLeftDeathAnim.bmp",
				pExpGemObejctPool,
				pMonsterObjPool
			);
			Scene* scene = SceneManager::GetSpecifiedScene(eSceneType::PLAY_SCENE);
			scene->AddGameObject(static_cast<GameObject*>(pMonster), eColliderLayer::MONSTER);
			return pMonster;
			break;
		}
		case eMonsterType::BOSS_MIRA:
			break;
		case eMonsterType::COUNT:
			assert(false);
			break;
		default:
			assert(false);
			break;
		}
		return nullptr;
	}
}