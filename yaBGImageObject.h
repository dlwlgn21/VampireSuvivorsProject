#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class BGImageObject : public GameObject
	{
	public:
		BGImageObject(const std::wstring& key, const std::wstring& path);
		virtual ~BGImageObject() = default;

		virtual void Initialize() = 0;
		virtual void Tick() = 0;
		virtual void Render(HDC hdc) = 0;
	protected:
		Image* mpImage;
	};
}

