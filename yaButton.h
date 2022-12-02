#pragma once
#include "yaUIBase.h"

namespace ya
{
	class Button : public UIBase
	{
	public:
		Button(eUIType type);
		virtual ~Button() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		virtual void Click();
	private:
		Event mOnClick;
		BLENDFUNCTION mBlendFunc;
		bool mbIsMouseOn;
	};

}

