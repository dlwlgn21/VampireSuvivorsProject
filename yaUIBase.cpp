#include "yaUIBase.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	UIBase::UIBase(eUIType type)
		: mUIType(type)
		, mbIsFullScreen(false)
		, mbIsEnable(false)
		, mParent(nullptr)
		, mPos(Vector2::ZERO)
		, mSize(Vector2::ZERO)
		, mpImage(nullptr)
	{
		mChilds.reserve(16);
	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		OnInitialize();
		for (UIBase* pChild : mChilds)
		{
			pChild->OnInitialize();
		}
	}

	void UIBase::Active()
	{
		mbIsEnable = true;
		OnActive();
		// 부모께 활성화 되면, 자식들 것도 활성화 되어야 함.
		for (UIBase* pChild : mChilds)
		{
			pChild->mbIsEnable = true;
			pChild->OnActive();
		}
	}

	void UIBase::Inactive()
	{
		// 부모께 비활성화 되면, 자식들 것도 비활성화 되어야 함. 자식들 것 먼저 꺼주어야 함.
		for (UIBase* pChild : mChilds)
		{
			pChild->OnInactive();
			pChild->mbIsEnable = false;
		}
		OnInactive();
		mbIsEnable = false;
	}

	void UIBase::Tick()
	{
		if (!mbIsEnable) 
			{ return; }

		OnTick();
		if (mParent != nullptr)
			{ mScreenPos = mParent->GetPos() + mPos; }
		else
			{ mScreenPos = mPos; }

		for (UIBase* pChild : mChilds)
		{
			if (pChild->mbIsEnable)
				{ pChild->Tick(); }
		}
	}

	void UIBase::Render(HDC hdc)
	{
		if (!mbIsEnable) 
			{ return; }
		OnRender(hdc);
		for (UIBase* pChild : mChilds)
		{
			if (pChild->mbIsEnable)
				{ pChild->OnRender(hdc); }
		}
	}

	void UIBase::UIClear()
	{
		for (UIBase* pChild : mChilds)
		{
			if (pChild->mbIsEnable)
			{
				pChild->OnUIClear();
			}
		}
		OnUIClear();
	}

	void UIBase::LoadUIImage(const std::wstring& key, const std::wstring& path)
	{
		mpImage = Resources::Load<Image>(key, path);
		assert(mpImage != nullptr);
		mSize = Vector2(static_cast<float>(mpImage->GetWidth()), static_cast<float>(mpImage->GetHeight()));
	}

	void UIBase::AddUIChild(UIBase* pUIBase)
	{
		assert(pUIBase != nullptr);
		mChilds.push_back(pUIBase);
		pUIBase->mParent = this;
	}

}