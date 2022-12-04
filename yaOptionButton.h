#pragma once
#include "yaButtonImageObject.h"

namespace ya
{
	class OptionButton final : public ButtonImageObject
	{
	public:
		OptionButton(const std::wstring& key, const std::wstring& path);

		virtual ~OptionButton() = default;
		OptionButton(const OptionButton& other) = delete;
		OptionButton& operator=(const OptionButton& other) = delete;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
	};
}

