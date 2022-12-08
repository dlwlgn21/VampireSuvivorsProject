#pragma once
#include "yaUIAnimObject.h"

namespace ya
{
	class TitleSceneExitUIButton final : public UIAnimObject
	{
	public:
		TitleSceneExitUIButton();
		TitleSceneExitUIButton(const TitleSceneExitUIButton& other) = delete;
		TitleSceneExitUIButton& operator=(const TitleSceneExitUIButton& other) = delete;
		virtual ~TitleSceneExitUIButton() = default;

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


