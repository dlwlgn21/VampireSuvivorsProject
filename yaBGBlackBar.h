#pragma once
#include "yaBGIMageObjectAlpha.h"

namespace ya
{
	class BGBlackBar : public BGImageObjectAlpha
	{
	public:
		BGBlackBar(const std::wstring& key, const std::wstring& path);
		BGBlackBar(const BGBlackBar& other) = delete;
		BGBlackBar& operator=(const BGBlackBar& other) = delete;
		virtual ~BGBlackBar() = default;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	private:
		BLENDFUNCTION mFunc;
	};
}

