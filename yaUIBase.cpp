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
		, mScreenPos(Vector2::ZERO)
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
		for (UIBase* pChild : mChilds)
		{
			pChild->mbIsEnable = true;
			pChild->OnActive();
		}
	}

	void UIBase::Inactive()
	{
		mbIsEnable = false;
		for (UIBase* pChild : mChilds)
		{
			pChild->OnInactive();
			pChild->mbIsEnable = false;
		}
		OnInactive();
	}

	void UIBase::Tick()
	{
		if (!mbIsEnable) 
			{ return; }

		OnTick();
		if (mParent != nullptr)
			{ mScreenPos = mParent->GetScreenPos() + mPos; }
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
		mChilds.push_back(pUIBase);
		pUIBase->mParent = this;
	}

}