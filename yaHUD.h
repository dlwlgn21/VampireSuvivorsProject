#pragma once
#include "yaUIBase.h"
namespace ya
{
	class HUD : public UIBase
	{
	public:
		HUD(eUIType type);
		virtual ~HUD() = default;

		virtual void OnInitialize() = 0;
		virtual void OnActive() = 0;
		virtual void OnInactive() = 0;
		virtual void OnTick() = 0;
		virtual void OnRender(HDC hdc) = 0;
		virtual void OnUIClear() = 0;

	protected:
		BLENDFUNCTION mBlendFunc;

	};

}

