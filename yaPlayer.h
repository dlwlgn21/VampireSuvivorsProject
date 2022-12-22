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
	class Axe;
	class FireWand;
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

		struct WeaponStat
		{
			unsigned char Damage;
			unsigned char Count;
			unsigned char PanetratingCount;
			float Speed;
			float ShootInterval;
			WeaponStat(unsigned char damage, unsigned char count, unsigned char panetratingCount, float speed, float shootInterval)
				: Damage(damage)
				, Count(count)
				, PanetratingCount(panetratingCount)
				, Speed(speed)
				, ShootInterval(shootInterval)
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
		void DamageFromMonster(const int damage);
		void IncreaseExp(const int exp);
		WeaponStat& GetWeaponStat(const eWeaponAndItemTypes type);
		void IncreaseWeaponStat(const eWeaponAndItemTypes type);
		void RestrictYTopPosition(float restricedYPos);
		void RestrictYBotPosition(float restricedYPos);
		void CanNotEnterPlayer(float leftXCoordinate, float rightXCoordinate, float topYCoordinate, float botYCoordinate);
		__forceinline void SetHp(const int hp) { mHp = hp; }
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
		__forceinline void IncreaseWeaponLevel(const eWeaponAndItemTypes type)
		{
			assert(static_cast<UINT>(type) <= static_cast<UINT>(eWeaponAndItemTypes::AXE));
			if (static_cast<UINT>(type) <= static_cast<UINT>(eWeaponAndItemTypes::AXE))
				{ ++mPlyerItemLevelStat.ItemLevels[static_cast<UINT>(type)]; }
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
		float mKnockbackValue;

		ePlayerAnimState mePlayerAnimState;
		ePlayerLookDirection meLookDir;
		KnifeObjectPool* mpKnifeObjPool;
		float mKnifeShootTimer;

		WeaponObjectPool<RuneTracer>* mpRuneObjPool;
		float mRuneShootTimer;

		WeaponObjectPool<Axe>* mpAxeObjPool;
		float mAxeShootTimer;

		WeaponObjectPool<FireWand>* mpFireWandObjPool;
		float mFireWandShootTimer;


		PlayerItemLevelStat mPlyerItemLevelStat;

		WeaponStat mKnifeStat;
		WeaponStat mFireWandStat;
		WeaponStat mRuneStat;
		WeaponStat mAxeStat;

		bool mbIsWeaponFireWandOpen;
		bool mbIsWeaponRuneOpen;
		bool mbIsWeaponAxeOpen;
	};

}

