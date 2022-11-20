#pragma once
#include "yaUIBase.h"

namespace ya
{
	class Panel : public UIBase
	{
	public:
		Panel(eUIType type);
		virtual ~Panel() = default;

		void OnInitialize() override;
		void OnActivate() override;
		void OnInActivate() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		void AddUIBase(UIBase* pUIBase);

	private:
		BLENDFUNCTION mBlendFunc;
	};

}

