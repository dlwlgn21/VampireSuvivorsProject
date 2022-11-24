#include "yaGameObejct.h"
#include "yaTime.h"

namespace ya
{
	GameObject::GameObject()
		: mPos(Vector2::ZERO)
		, mScale(Vector2::ONE)
		, mIsAlive(true)
		, mDeathTime(-100.0f)
		, mbDeathTriggerFlag(false)
	{
		mComponents.reserve(static_cast<UINT>(eComponentType::COUNT));
	}

	GameObject::GameObject(Vector2 pos)
		: mPos(pos)
		, mScale(Vector2::ONE)
		, mIsAlive(true)
		, mDeathTime(-100.0f)
		, mbDeathTriggerFlag(false)
	{
		mComponents.reserve(static_cast<UINT>(eComponentType::COUNT));
	}

	GameObject::~GameObject()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr) 
				{ continue; }
			delete component;
			component = nullptr;
		}
	}
	void GameObject::Initialize()
	{
	}

	void GameObject::Tick()
	{
		if (mbDeathTriggerFlag)
		{
			mDeathTime -= Time::DeltaTime();
			if (mDeathTime <= 0.0f)
				{ DisableObject(); }
		}

		// 모든 컴포넌트의 Tick 호출
		for (Component* component : mComponents)
		{
			if (component == nullptr) 
				{ continue; }
			component->Tick();
		}
	}
	void GameObject::Render(HDC hdc)
	{
		// 모든 컴포넌트의 Render 호출
		for (Component* component : mComponents)
		{
			if (component == nullptr) 
				{ continue; }
			component->Render(hdc);
		}
	}
	void GameObject::OnCollisionEnter(Collider* other)
	{
	}

	void GameObject::OnCollisionStay(Collider* other)
	{
	}

	void GameObject::OnCollisionExit(Collider* other)
	{
	}

	inline void GameObject::SetDisableTime(float time)
	{
		if (mDeathTime <= 0.0f)
		{
			mDeathTime = time;
			mbDeathTriggerFlag = true;
		}
	}

	void GameObject::AddComponent(Component* component)
	{
		assert(component != nullptr);
		mComponents.push_back(component);
		component->mOwner = this;
	}

}