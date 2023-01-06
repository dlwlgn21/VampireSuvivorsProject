#pragma once
#include "yaGameObejct.h"
#include "yaPlayer.h"

const constexpr UINT MAX_KEY_LENGTH = 32;
const constexpr UINT MAX_PATH_LENGTH = 64;

namespace ya
{
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

	enum class eMonsterState
	{
		PATROL,
		TRACE,
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
		Monster(
			const MonsterCreateInfo& monInfo,
			const std::wstring& imageRightMoveKey,
			const std::wstring& imageLeftMoveKey,
			const std::wstring& imageRightDeathKey,
			const std::wstring& imageLeftDeathKey,
			const std::wstring& imageRightHittedKey,
			const std::wstring& imageLeftHittedKey,


			const std::wstring& imageRightMovePath,
			const std::wstring& imageLeftMovePath,
			const std::wstring& imageRightDeathPath,
			const std::wstring& imageLeftDeathPath,
			const std::wstring& imageRightHittedPath,
			const std::wstring& imageLeftHittedPath,
			ExpGemObjPool* pExpGemObjPool,
			MonsterObjPool<Monster>* pMonsterObjPool
		);
		virtual ~Monster();

		virtual void Tick();
		virtual void Render(HDC hdc);
		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);
		
		__forceinline Vector2 GetSize() const { return mAnimMoveSize; }
		__forceinline int GetDamage() const { return mDamage; }
		__forceinline int GetHP() const { return mHP; }
		__forceinline void SetHP(int hp) { mHP = hp; }
		__forceinline Vector2 GetVectorToPlayer() const 
		{
			return Vector2(mPlayerPos - mPos);
		}
	protected:
		void CountHitAnimationTimer();

	protected:
		Player* mpPlayer;
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
		Image* mpRightHittedImage;
		Image* mpLeftHittedImage;
		Animator* mpAnimator;
		Collider* mpCollider;

		const std::wstring mImageRightMoveKey;
		const std::wstring mImageLeftMoveKey;
		const std::wstring mImageRightHittedKey;
		const std::wstring mImageLeftHittedKey;
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
		bool mbIsHittedFromWeapon;
		float mAnimDeathCounter;
		float mAnimHittedCounter;
		float mAnimHittedTime;
		int mDisplayWeaponDamage;
		float mR;
		float mG;
		float mB;
		float mRecogRange;
		eMonsterState meCurrState;
		LOGFONT mFont;
		HWND mHwnd;
		ExpGemObjPool* mpExpGemObjPool;
		MonsterObjPool<Monster>* mpMonsterObjPool;
	};
}

