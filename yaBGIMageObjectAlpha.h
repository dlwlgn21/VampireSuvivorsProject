#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class BGImageObjectAlpha : public GameObject
	{
	public:
		BGImageObjectAlpha(const std::wstring& key, const std::wstring& path);
		virtual ~BGImageObjectAlpha() = default;

		virtual void Initialize() = 0;
		virtual void Tick() = 0;
		virtual void Render(HDC hdc) = 0;
	protected:
		Image* mpImage;
	};

}

