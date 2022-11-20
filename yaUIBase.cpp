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

	void UIBase::Activate()
	{
		mbIsEnable = true;
		OnActivate();
		for (UIBase* pChild : mChilds)
		{
			pChild->mbIsEnable = true;
			pChild->OnActivate();
		}
	}

	void UIBase::InActivate()
	{
		mbIsEnable = false;
		for (UIBase* pChild : mChilds)
		{
			pChild->OnInActivate();
			pChild->mbIsEnable = false;
		}
		OnInActivate();
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
			{
				pChild->OnRender(hdc);
			}
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
		mSize = Vector2(mpImage->GetWidth(), mpImage->GetHeight());
	}

	void UIBase::AddUIChild(UIBase* pUIBase)
	{
		mChilds.push_back(pUIBase);
		pUIBase->mParent = this;
	}

}