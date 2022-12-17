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
	public:
		struct PlayerItemLevelStat 
		{
			unsigned char ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::COUNT)];
			PlayerItemLevelStat()
				: ItemLevels{0, }
			{
				ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::KNIFE)] = 1;
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
		__forceinline void IncreaseWeaponDamageCoefficient() 
		{ 
			++mPlyerItemLevelStat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_DAMAGE)];
			mWeaponDamageCoefficient += 0.1f; 
		}
		__forceinline void IncreaseWeaponSpeedCoefficient() 
		{ 
			++mPlyerItemLevelStat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::WEAPON_SPEED)];
			mWeaponSpeedCoefficient += 0.1f; 
		}
		__forceinline void IncreaseAmour() 
		{ 
			++mPlyerItemLevelStat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::PLAYER_AMOUR)];
			++mAmour; 
		}
		__forceinline void IncreaseMoveSpeed()
		{
			++mPlyerItemLevelStat.ItemLevels[static_cast<UINT>(eWeaponAndItemTypes::MOVE_SPEED)];
			mMoveSpeed *= 1.1f; 
		}
		const PlayerItemLevelStat& GetItemLevelStat() const { return mPlyerItemLevelStat; }

	private:
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

		// Upgradable
		int mAmour;
		float mMoveSpeed;
		float mWeaponSpeed;
		float mWeaponDamageCoefficient;
		float mWeaponSpeedCoefficient;

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

