#pragma once
#include "yaUIAnimObject.h"

namespace ya
{
	class TitleSceneOptionUIButton final : public UIAnimObject
	{
	public:
		TitleSceneOptionUIButton();
		TitleSceneOptionUIButton(const TitleSceneOptionUIButton& other) = delete;
		TitleSceneOptionUIButton& operator=(const TitleSceneOptionUIButton& other) = delete;
		virtual ~TitleSceneOptionUIButton() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
		void ButtonClicked() override;
	private:
		int mImgWidth;
		int mImgHeight;
	};
}

