#pragma once
#include "yaBGImageObject.h"

namespace ya
{
	class ResultImage final : public BGImageObject
	{
	public:
		ResultImage(const std::wstring& key, const std::wstring& path);
		ResultImage(const ResultImage& other) = delete;
		ResultImage& operator=(const ResultImage& other) = delete;
		virtual ~ResultImage() = default;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	private:
	};
}

