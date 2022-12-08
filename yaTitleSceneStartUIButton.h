#pragma once
#include "yaUIAnimObject.h"

namespace ya
{
	class TitleSceneStartUIButton final : public UIAnimObject
	{
	public:
		TitleSceneStartUIButton();
		TitleSceneStartUIButton(const TitleSceneStartUIButton& other) = delete;
		TitleSceneStartUIButton& operator=(const TitleSceneStartUIButton& other) = delete;
		virtual ~TitleSceneStartUIButton() = default;

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

