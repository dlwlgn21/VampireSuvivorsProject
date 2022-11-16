#include "yaGameObejct.h"
#include "yaRigidBody.h"
#include "yaTime.h"
namespace ya
{
	RigidBody::RigidBody()
		: Component(eComponentType::RIGID_BODY)
		, mMess(1.0f)
		, mFriction(100.0f)
		, mForce(Vector2::ZERO)
		, mVelocity(Vector2::ZERO)
		, mAccelation(Vector2::ZERO)
		, mbIsGrounded(false)
		, mGravity(Vector2(0.0f, 300.0f))
		, mLimitVelocity(Vector2(200.0f, 1000.0f))
	{
	}
	RigidBody::~RigidBody()
	{
	}
	void RigidBody::Tick()
	{
		//// 힘		= 질량 * 가속도	F = M * A
		//// 가속도	= 힘 / 질량		A = F / M
		//mAccelation = mForce / mMess;
		//mVelocity += (mAccelation * Time::DeltaTime());
		//
		//if (mbIsGrounded)
		//{
		//	Vector2 gravity = mGravity;
		//	gravity.Normalize();
		//	float dotLength = yamath::Dot(mVelocity, gravity);
		//	gravity -= gravity * dotLength;
		//}
		//else
		//{
		//	mVelocity += mGravity * Time::DeltaTime();
		//}

		//// 최대 속도 제한
		//Vector2 gravity = mGravity;
		//gravity.Normalize();
		//float dotLength = yamath::Dot(mVelocity, gravity);
		//gravity = gravity * dotLength;

		//Vector2 sideVelocity = mVelocity - gravity;
		//if (mLimitVelocity.y < gravity.GetLength())
		//{
		//	gravity.Normalize();
		//	gravity *= mLimitVelocity.y;
		//}
		//if (mLimitVelocity.x < sideVelocity.GetLength())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitVelocity.x;
		//}
		//mVelocity = gravity + sideVelocity;


		//// 마찰력 조건 (적용된 힘이 없고, 속도가 0이 아닐때)
		//if (mVelocity != Vector2::ZERO)
		//{
		//	// 마찰력은 속도의 반대방향으로 적용이 되어야 함
		//	Vector2 friction = -mVelocity;
		//	// 마찰력에 해당하는 벡터를 구해온다.
		//	friction =  friction.Normalize() * mFriction * mMess * Time::DeltaTime();
		//	
		//	// 마찰력만큼 감속을 시켜주어야 함. -했기 때문에 더해줌.
		//	if (mVelocity.GetLength() < friction.GetLength())	
		//	{ mVelocity = Vector2::ZERO; }
		//	else												
		//	{ mVelocity += friction; }

		//}

		//// 속도에 맞춰 물체를 이동시킴
		//Vector2 pos = GetOwner()->GetPos();
		//pos = pos + (mVelocity * Time::DeltaTime());
		//GetOwner()->SetPos(pos);
		//mForce.Clear();



		//이동
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMess;

		// 속도에 가속도를 더한다
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbIsGrounded)
		{
			// 땅위에 있을때
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = yamath::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// 공중에 있을 때
			mVelocity += mGravity * Time::DeltaTime();
		}


		// 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = yamath::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.GetLength())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.GetLength())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		//마찰력 조건 ( 적용된 힘이 없고, 속도가 0 이 아닐 떄)
		if (!(mVelocity == Vector2::ZERO))
		{
			// 속도에 반대 방향으로 마찰력을 적용
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMess * Time::DeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.GetLength() < friction.GetLength())
			{
				// 속도를 0 로 만든다.
				mVelocity = Vector2(0.f, 0.f);
			}
			else
			{
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				mVelocity += friction;
			}
		}

		// 속도에 맞게 물체를 이동시킨다.
		Vector2 pos = GetOwner()->GetPos();
		pos = pos + mVelocity * Time::DeltaTime();
		GetOwner()->SetPos(pos);
		mForce.Clear();

	}
	void RigidBody::Render(HDC hdc)
	{
	}

	void RigidBody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}