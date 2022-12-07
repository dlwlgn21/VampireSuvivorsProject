#pragma once
#include "yaHUD.h"

namespace ya
{
	class Image;
	class SelectionMenuIcon : public HUD
	{
	public:
		SelectionMenuIcon(const std::wstring& key, const std::wstring& path);
		SelectionMenuIcon(const SelectionMenuIcon& other) = delete;
		SelectionMenuIcon& operator=(const SelectionMenuIcon& other) = delete;
		virtual ~SelectionMenuIcon() = default;

		virtual void OnInitialize() = 0;
		virtual void OnActive() = 0;
		virtual void OnInactive() = 0;
		virtual void OnTick() = 0;
		virtual void OnRender(HDC hdc)= 0;
		virtual void OnUIClear() = 0;

		void ChangeRenderImage();
	protected:
		Image* mpCurrRenderImage;
		Image* mpSelectedImage;
	};
}


