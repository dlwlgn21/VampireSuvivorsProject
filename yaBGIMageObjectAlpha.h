#pragma once
#include "yaGameObejct.h"

namespace ya
{
	class Image;
	class BGImageObjectAlpha final : public GameObject
	{
	public:
		BGImageObjectAlpha(const std::wstring key);
		virtual ~BGImageObjectAlpha();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	private:
		Image* mpImage;
		std::wstring mKey;
		BLENDFUNCTION mFunc;
	};

}

