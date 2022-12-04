#pragma once
#include "yaBGImageObject.h"

namespace ya
{
	class BGGmaeImage final : public BGImageObject 
	{
	public:
		BGGmaeImage(const std::wstring& key, const std::wstring& path);
		BGGmaeImage(const BGGmaeImage& other) = delete;
		BGGmaeImage& operator=(const BGGmaeImage& other) = delete;
		virtual ~BGGmaeImage() = default;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	};
}

