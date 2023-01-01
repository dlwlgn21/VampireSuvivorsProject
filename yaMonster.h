#pragma once
#include "yaGameObejct.h"
#include "yaPlayer.h"

namespace ya
{
	class AI;
	class Player;
	class Monster : public GameObject
	{
	public:
		Monster(Vector2 pos, Player* pPlayer, int hp, int damage, int exp, float speed);
		virtual ~Monster();

		virtual void Tick();
		virtual void Render(HDC hdc) = 0;
		virtual void OnCollisionEnter(Collider* other) = 0;
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

		__forceinline void SetAI(AI* pAI) { assert(pAI != nullptr); mpAI = pAI; }

	protected:
		Player* mpPlayer;
		AI* mpAI;
		int mHP;
		int mDamage;
		int mExp;
		float mSpeed;
		Vector2 mPlayerPos;
	};
}

