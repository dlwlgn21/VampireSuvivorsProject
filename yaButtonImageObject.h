#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class ButtonImageObject final : public GameObject
	{
	public:
		ButtonImageObject(const std::wstring key);
		virtual ~ButtonImageObject();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	private:
		Image* mpImage;
		std::wstring mKey;
	};

}

