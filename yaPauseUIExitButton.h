#pragma once
#include "yaUIAnimObject.h"

namespace ya
{
	class PauseUIExitButton final : public UIAnimObject
	{
	public:
		PauseUIExitButton();
		PauseUIExitButton(const PauseUIExitButton& other) = delete;
		PauseUIExitButton& operator=(const PauseUIExitButton& other) = delete;
		virtual ~PauseUIExitButton() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
		void ButtonClicked() override;

		__forceinline bool IsSelected() { return mbIsSelected; }
		__forceinline void SetIsSelected(bool isSelected) { mbIsSelected = isSelected; }
	private:
		int mImgWidth;
		int mImgHeight;
	};
}

