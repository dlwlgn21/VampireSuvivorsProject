#pragma once
#include "yaGameObejct.h"
#include "yaPlayer.h"

namespace ya
{
	class Player;
	class Monster : public GameObject
	{
	public:
		Monster(Vector2 pos, Player* pPlayer, int hp, int damage, int exp, float speed);
		virtual ~Monster() = default;

		virtual void Tick();
		virtual void Render(HDC hdc) = 0;
		void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other) = 0;
		virtual void OnCollisionExit(Collider* other) = 0;
		

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

	protected:
		__forceinline void SetVelocity()
		{
			float distance = GetVectorToPlayer().GetLength();
			Vector2 playerPos = mpPlayer->GetPos();
			if (std::abs(distance) <= FLT_EPSILON)
			{
				mVelocityX = 0.0f;
				mVelocityY = mSpeed;
			}
			else
			{
				mVelocityX = (mPos.x - playerPos.x) / distance * mSpeed;
				mVelocityY = (mPos.y - playerPos.y) / distance * mSpeed;
			}
		}

	protected:
		Player* mpPlayer;
		int mHP;
		int mDamage;
		int mExp;
		float mSpeed;
		float mVelocityX;
		float mVelocityY;
		Vector2 mPlayerPos;
	};
}

