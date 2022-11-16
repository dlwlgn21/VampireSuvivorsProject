#pragma once
#include "Common.h"
#include "yaComponent.h"

namespace ya
{
	class RigidBody final : public Component
	{
	public:
		RigidBody();
		~RigidBody();

		void Tick() override;
		void Render(HDC hdc) override;

		void AddForce(Vector2 force);
		__forceinline void SetMass(float mess) { mMess = mess; }
		__forceinline void SetIsGround(bool isGrounded) { mbIsGrounded = isGrounded; }
		__forceinline Vector2 GetVelocity() { return mVelocity; }
		__forceinline void SetVelocity(Vector2 velocity) { mVelocity = velocity; }


	private:
		// 힘과 마찰력을 이용한 운동
		float mMess;
		float mFriction;
		Vector2 mForce;
		Vector2 mVelocity;
		Vector2 mAccelation;

		// 중력을 잉한 점프
		bool mbIsGrounded;
		Vector2 mGravity;
		Vector2 mLimitVelocity;

	};
}

