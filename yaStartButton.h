#pragma once
#include "yaButtonImageObject.h"

namespace ya
{
	class Image;
	class StartButton final : public ButtonImageObject
	{
	public:
		StartButton(const std::wstring& key, const std::wstring& path);

		virtual ~StartButton() = default;
		StartButton(const StartButton& other) = delete;
		StartButton& operator=(const StartButton& other) = delete;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	};
}

