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
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		void AddUIBase(UIBase* pUIBase);

	private:
		std::vector<UIBase*> mChilds;
		BLENDFUNCTION mBlendFunc;
	};

}

