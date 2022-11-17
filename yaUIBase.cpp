#include "yaUIBase.h"

namespace ya
{
	UIBase::UIBase(eUIType type)
		: mUIType(type)
		, mbIsFullScreen(false)
		, mbIsEnable(false)
	{
	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{

	}

	void UIBase::Activate()
	{
	}

	void UIBase::InActivate()
	{
	}

	void UIBase::Tick()
	{
	}

	void UIBase::Render(HDC hdc)
	{
	}

	void UIBase::UIClear()
	{
	}

}