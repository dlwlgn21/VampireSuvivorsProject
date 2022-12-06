#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class ButtonImageObject : public GameObject
	{
	public:
		ButtonImageObject(const std::wstring& key, const std::wstring& path);
		virtual ~ButtonImageObject() = default;

		virtual void Initialize() = 0;
		virtual void Tick() = 0;
		virtual void Render(HDC hdc) = 0;
		virtual void ButtonClicked() = 0;
		__forceinline bool IsSelected() const { return mbIsSelected; }
		__forceinline void SetIsSelected(bool isSelected) { mbIsSelected = isSelected; }
	protected:
		Image* mpImage;
		bool mbIsSelected;
	};

}

