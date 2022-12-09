#pragma once
#include "yaUIAnimObject.h"

namespace ya
{
	class PauseUIContinueButton final : public UIAnimObject
	{
	public:
		PauseUIContinueButton();
		PauseUIContinueButton(const PauseUIContinueButton& other) = delete;
		PauseUIContinueButton& operator=(const PauseUIContinueButton& other) = delete;
		virtual ~PauseUIContinueButton() = default;

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

