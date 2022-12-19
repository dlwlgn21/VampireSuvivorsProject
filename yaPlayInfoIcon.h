#pragma once
#include "yaHUD.h"

namespace ya
{
	enum class ePlayInfoIconPos
	{
		TOP,
		BOT,
		COUNT
	};

	class PlayInfoIcon : public HUD
	{
	public:
		PlayInfoIcon(eUIType eUiType, ePlayInfoIconPos ePos, eWeaponAndItemTypes eItemType, Vector2 pos);
		PlayInfoIcon(const PlayInfoIcon& other) = delete;
		PlayInfoIcon& operator=(const PlayInfoIcon& other) = delete;
		virtual ~PlayInfoIcon() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;

	protected:
		ePlayInfoIconPos meIconPos;
		int mImgWidth;
		int mImgHeight;
	};
}

