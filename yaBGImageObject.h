#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class BGImageObject final : public GameObject
	{
	public:
		BGImageObject(const std::wstring key);
		virtual ~BGImageObject();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	private:
		Image* mpImage;
		std::wstring mKey;
	};
}

