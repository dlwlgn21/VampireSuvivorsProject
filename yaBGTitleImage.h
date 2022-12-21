#pragma once
#include "yaBGImageObject.h"

namespace ya
{
	class BGTitleImage final : public BGImageObject
	{
	public:
		BGTitleImage(const std::wstring& key, const std::wstring& path);
		BGTitleImage(const BGTitleImage& other) = delete;
		BGTitleImage& operator=(const BGTitleImage& other) = delete;
		virtual ~BGTitleImage() = default;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	};
}

