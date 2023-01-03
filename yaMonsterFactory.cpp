#include "yaMonsterFactory.h"
#include "yaMonster.h"
#include "yaMudman.h"
#include "yaPlayer.h"
#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaObjectPool.h"
#include "yaExpGemObjPool.h"
#include "yaMonsterObjPool.h"

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
			break;
		}
		case eMonsterType::GHOST:
			break;
		case eMonsterType::MEDUSA_HEAD:
			break;
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