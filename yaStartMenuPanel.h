#pragma once
#include "yaPanel.h"

namespace ya
{
	enum class eStartSelection
	{
		START,
		OPTION,
		EXIT,
		COUNT
	};
	class UIAnimObject;
	class StartMenuPanel final : public Panel
	{
	public:
		StartMenuPanel();
		virtual ~StartMenuPanel() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

		void SetButtonPtr();
	private:
		bool mbIsUpKeyDown;
		bool mbIsCharacterSelectionUIPoped;
		UIAnimObject* mpButtonsPtr[static_cast<UINT>(eStartSelection::COUNT)];
	};
}

