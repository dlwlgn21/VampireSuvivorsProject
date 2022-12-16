#pragma once
#include "yaUIAnimObject.h"

namespace ya
{
	class LevelUpArrow final : public UIAnimObject
	{
	public:
		LevelUpArrow();
		LevelUpArrow(const LevelUpArrow& other) = delete;
		LevelUpArrow& operator=(const LevelUpArrow& other) = delete;
		virtual ~LevelUpArrow() = default;

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
		const float M_MOVE_AMOUNT;
		const int M_MAX_UP_POS;
		const int M_MIN_DOWN_POS;
	};
}