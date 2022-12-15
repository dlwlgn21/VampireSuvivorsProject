#pragma once
#include "yaGameObejct.h"
#include "yaPlayerCustomAnimator.h"

namespace ya
{
	enum class ePlayerLookDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UP_LEFT,
		UP_RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT,
		COUNT
	};
	class KnifeObjectPool;
	class Image;
	class Collider;
	class RuneTracer;
	template<typename T> class WeaponObjectPool;
	class Player final : public GameObject
	{
		struct PlayerItemLevelStat
		{
			unsigned char WeaponKnifeLevel;
			unsigned char WeaponFireWandLevel;
			unsigned char WeaponRuneLevel;
			unsigned char WeaponAxeLevel;
			unsigned char WeaponSpeedLevel;
			unsigned char WeaponDamageLevel;
			unsigned char PlayerMoveSpeedLevel;
			unsigned char PlayerAmourLevel;
			PlayerItemLevelStat()
				: WeaponKnifeLevel(1)
				, WeaponFireWandLevel(0)
				, WeaponRuneLevel(0)
				, WeaponAxeLevel(0)
				, WeaponSpeedLevel(0)
				, WeaponDamageLevel(0)
				, PlayerMoveSpeedLevel(0)
				, PlayerAmourLevel(0)
			{
			}
		};
	public:
		Player();
		virtual ~Player();

		void Tick() override;
		void Render(HDC hdc) override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void WalkComplete();
		void DamageFromMonster(int damage);
		void IncreaseExp(int exp);

		__forceinline void SetHp(int hp) { mHp = hp; }
		__forceinline int GetHp() const { return mHp; }
		__forceinline int GetExp() const { return mExp; }
		__forceinline int GetLevel() const { return mLevel; }
		__forceinline PlayerItemLevelStat GetItemStat() { return mPlyerItemLevelStat; }

	private:
		float mSpeed;
		HPEN mPen;
		HBRUSH mBrush;
		Image* mpLeftImage;
		Image* mpRightImage;
		Image* mpLeftHittedImage;
		Image* mpRightHittedImage;
		PlayerCustomAnimator* mpAnimator;
		Collider* mpCollider;

		Vector2 mAnimSize;
		Vector2 mAnimOffset;
		UINT mAnimCount;
		float mMinAnimInterval;

		Vector2 dir;

		int mLevel;
		int mExp;
		int mHp;
		ePlayerAnimState mePlayerAnimState;
		ePlayerLookDirection meLookDir;
		float mKnifeShootInterval;
		float mKnifeShootTimer;

		KnifeObjectPool* mpKnifeObjPool;
		int mCurrKnifeCount;
		float mKnockbackValue;
		PlayerItemLevelStat mPlyerItemLevelStat;
	};

}

