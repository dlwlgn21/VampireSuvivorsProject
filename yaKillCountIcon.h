#pragma once
#include "yaBGImageObject.h"

namespace ya
{
	class KillCountIcon final : public BGImageObject
	{
	public:
		KillCountIcon(const std::wstring& key, const std::wstring& path);
		virtual ~KillCountIcon() = default;
		KillCountIcon(const KillCountIcon& other) = delete;
		KillCountIcon& operator=(const KillCountIcon& other) = delete;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

	private:

	};
}