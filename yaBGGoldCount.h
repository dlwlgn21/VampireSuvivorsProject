#pragma once
#include "yaBGImageObject.h"


namespace ya
{
	class BGGoldCount final : public BGImageObject
	{
	public:
		BGGoldCount(const std::wstring& key, const std::wstring& path);
		BGGoldCount(const BGGoldCount& other) = delete;
		BGGoldCount& operator=(const BGGoldCount& other) = delete;
		virtual ~BGGoldCount() = default;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	};
}

