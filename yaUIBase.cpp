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
	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		OnInitialize();
	}

	void UIBase::Activate()
	{
		mbIsEnable = true;
		OnActivate();
	}

	void UIBase::InActivate()
	{
		mbIsEnable = false;
		OnInActivate();
	}

	void UIBase::Tick()
	{
		if (!mbIsEnable) 
		{ return; }
		OnTick();
	}

	void UIBase::Render(HDC hdc)
	{
		if (!mbIsEnable) 
		{ return; }
		OnRender(hdc);

	}

	void UIBase::UIClear()
	{
		OnUIClear();
	}

	void UIBase::LoadUIImage(const std::wstring& key, const std::wstring& path)
	{
		mpImage = Resources::Load<Image>(key, path);
		mSize = Vector2(mpImage->GetWidth(), mpImage->GetHeight());
	}

}