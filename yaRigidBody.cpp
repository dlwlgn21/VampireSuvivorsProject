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
		//// ��		= ���� * ���ӵ�	F = M * A
		//// ���ӵ�	= �� / ����		A = F / M
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

		//// �ִ� �ӵ� ����
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


		//// ������ ���� (����� ���� ����, �ӵ��� 0�� �ƴҶ�)
		//if (mVelocity != Vector2::ZERO)
		//{
		//	// �������� �ӵ��� �ݴ�������� ������ �Ǿ�� ��
		//	Vector2 friction = -mVelocity;
		//	// �����¿� �ش��ϴ� ���͸� ���ؿ´�.
		//	friction =  friction.Normalize() * mFriction * mMess * Time::DeltaTime();
		//	
		//	// �����¸�ŭ ������ �����־�� ��. -�߱� ������ ������.
		//	if (mVelocity.GetLength() < friction.GetLength())	
		//	{ mVelocity = Vector2::ZERO; }
		//	else												
		//	{ mVelocity += friction; }

		//}

		//// �ӵ��� ���� ��ü�� �̵���Ŵ
		//Vector2 pos = GetOwner()->GetPos();
		//pos = pos + (mVelocity * Time::DeltaTime());
		//GetOwner()->SetPos(pos);
		//mForce.Clear();



		//�̵�
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMess;

		// �ӵ��� ���ӵ��� ���Ѵ�
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbIsGrounded)
		{
			// ������ ������
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = yamath::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// ���߿� ���� ��
			mVelocity += mGravity * Time::DeltaTime();
		}


		// �ִ� �ӵ� ����
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

		//������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ��)
		if (!(mVelocity == Vector2::ZERO))
		{
			// �ӵ��� �ݴ� �������� �������� ����
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMess * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (mVelocity.GetLength() < friction.GetLength())
			{
				// �ӵ��� 0 �� �����.
				mVelocity = Vector2(0.f, 0.f);
			}
			else
			{
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
				mVelocity += friction;
			}
		}

		// �ӵ��� �°� ��ü�� �̵���Ų��.
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