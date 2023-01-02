#pragma once
#include "yaGameObejct.h"
#include "yaPlayer.h"

#define MAX_KEY_LENGTH (32)
#define MAX_PATH_LENGTH (64)

namespace ya
{
	class AI;
	class Player;
	class Animator;
	class Collider;
	class ExpGem;
	class ExpGemObjPool;
	template<typename T> class MonsterObjPool;

	enum class eMonsterLookDir
	{
		LEFT,
		RIGHT,
		COUNT
	};
	struct MonsterCreateInfo
	{
		Vector2 Pos;
		Player* PtrPlayer;
		int Hp;
		int Damage;
		int Exp;
		float Speed;
		Vector2 AnimMoveSize;
		Vector2 AnimDeathSize;
		Vector2 AnimOffset;
		UINT AnimImageCount;
		UINT AnimDeathImageCount;
		float AnimDuration;
		float AnimDeathDuration;

		MonsterCreateInfo(
			Vector2 pos, 
			Player* pPlayer, 
			int hp, 
			int damage, 
			int exp,
			float speed,
			Vector2 animMoveSize,
			Vector2 animDeathSize,
			Vector2 animOffset,
			UINT animImageCount,
			UINT animDeathImageCount,
			float animDuration,
			float animDeathDuration
		)
			: Pos (pos)
			, PtrPlayer(pPlayer)
			, Hp(hp)
			, Damage(damage)
			, Exp(exp)
			, Speed(speed)
			, AnimMoveSize(animMoveSize)
			, AnimDeathSize(animDeathSize)
			, AnimOffset(animOffset)
			, AnimImageCount(animImageCount)
			, AnimDeathImageCount(animDeathImageCount)
			, AnimDuration(animDuration)
			, AnimDeathDuration(animDeathDuration)
		{
		}
	};

	class Monster : public GameObject
	{
	public:
		Monster(const MonsterCreateInfo& monInfo,
			const std::wstring& imageRightMoveKey,
			const std::wstring& imageLeftMoveKey,
			const std::wstring& imageRightDeathKey,
			const std::wstring& imageLeftDeathKey,

			const std::wstring& imageRightMovePath,
			const std::wstring& imageLeftMovePath,
			const std::wstring& imageRightDeathPath,
			const std::wstring& imageLeftDeathPath,
			ExpGemObjPool* pExpGemObjPool,
			MonsterObjPool<Monster>* pMonsterObjPool
		);
		virtual ~Monster();

		virtual void Tick();
		virtual void Render(HDC hdc) = 0;
		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);
		
		__forceinline Vector2 GetSize() const { return mAnimMoveSize; }
		__forceinline int GetDamage() const { return mDamage; }
		__forceinline int GetHP() const { return mHP; }
		__forceinline void SetHP(int hp) { mHP = hp; }
		__forceinline void DamagedFromWeapon(int damage) 
		{ 
			mHP -= damage; 
			if (mHP <= 0)
			{
				mbIsAlive = false;
				assert(mpPlayer != nullptr);
				//mExp -= mpPlayer->GetLevel();
				//if (mExp <= 1)
				//{
				//	mExp -= 0.02f;
				//}
				mpPlayer->IncreaseExp(mExp);
			}
		};
		__forceinline Vector2 GetVectorToPlayer() const 
		{
			return Vector2(mPlayerPos - mPos);
		}

		__forceinline void SetAI(AI* pAI) 
		{ 
			assert(pAI != nullptr); 
			mpAI = pAI;
			//mpAI->S
		}

	protected:
		Player* mpPlayer;
		AI* mpAI;
		int mHP;
		int mDamage;
		int mExp;
		float mSpeed;
		Vector2 mPlayerPos;
		eMonsterLookDir meLookDir;

		Image* mpRightImage;
		Image* mpLeftImage;
		Image* mpRightDeathImage;
		Image* mpLeftDeathImage;
		Animator* mpAnimator;
		Collider* mpCollider;

		const std::wstring mImageRightMoveKey;
		const std::wstring mImageLeftMoveKey;
		const std::wstring mImageRightDeathKey;
		const std::wstring mImageLeftDeathKey;

		Vector2 mAnimMoveSize;
		Vector2 mAnimDeathSize;
		Vector2 mAnimOffset;
		UINT mAnimImageCount;
		UINT mAnimDeathImageCount;
		float mAnimDuration;
		float mAnimDeathDuration;
		bool mbIsDeathFromWeapon;
		float mAnimDeathCounter;

		ExpGemObjPool* mpExpGemObjPool;
		MonsterObjPool<Monster>* mpMonsterObjPool;
	};
}

