#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Monster : public GameObject
	{
	public:
		Monster(Vector2 pos, int hp);
		virtual ~Monster() = default;

		virtual void Tick() = 0;
		virtual void Render(HDC hdc) = 0;
		virtual void OnCollisionEnter(Collider* other) = 0;
		virtual void OnCollisionStay(Collider* other) = 0;
		virtual void OnCollisionExit(Collider* other) = 0;
		
		__forceinline int GetHP() { return mHP; }
		__forceinline void SetHP(int hp) { mHP = hp; }
		__forceinline void DamagedFromWeapon(int damage) 
		{ 
			mHP -= damage; 
			if (mHP <= 0)
			{
				mbIsAlive = false;
			}
		
		};

	protected:
		int mHP;
	};
}

