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
		, mScreenPos(Vector2::ZERO)
	{
		mChilds.reserve(8);
	}

	UIBase::~UIBase()
	{
		for (UIBase* pChild : mChilds)
		{
			if (pChild != nullptr)
				{ delete pChild; }
		}
	}

	void UIBase::Initialize()
	{
		OnInitialize();
		for (UIBase* pChild : mChilds)
		{
			pChild->Initialize();
		}
	}

	void UIBase::Active()
	{
		mbIsEnable = true;
		OnActive();
		// �θ� Ȱ��ȭ �Ǹ�, �ڽĵ� �͵� Ȱ��ȭ �Ǿ�� ��.
		for (UIBase* pChild : mChilds)
		{
			pChild->mbIsEnable = true;
			pChild->Active();
		}
	}

	void UIBase::Inactive()
	{
		// �θ� ��Ȱ��ȭ �Ǹ�, �ڽĵ� �͵� ��Ȱ��ȭ �Ǿ�� ��. �ڽĵ� �� ���� ���־�� ��.
		for (UIBase* pChild : mChilds)
		{
			pChild->Inactive();
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
				{ pChild->Render(hdc); }
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