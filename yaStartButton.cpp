#include "yaStartButton.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaUIManager.h"


namespace ya
{
	StartButton::StartButton(const std::wstring& key, const std::wstring& path)
		: ButtonImageObject(key, path)
		, mbIsSelected(false)
	{
		mPos = Vector2(1200/2 + 15.0f, 900/2 + 60.0f);
	}
	void StartButton::Initialize()
	{
	}
	void StartButton::Tick()
	{
		GameObject::Tick();
		
		if (IS_KEY_DOWN(eKeyCode::Q) && !mbIsSelected)
		{
			UIManager::Push(eUIType::CHARACTER_SELECTION);
			mbIsSelected = true;
		}

		if (IS_KEY_DOWN(eKeyCode::R) && mbIsSelected)
		{
			UIManager::Pop(eUIType::CHARACTER_SELECTION);
			mbIsSelected = false;
		}
	}
	void StartButton::Render(HDC hdc)
	{
		TransparentBlt(
			hdc,
			static_cast<int>(mPos.x),
			static_cast<int>(mPos.y),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			0,
			0,
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),
			RGB(255, 0, 255)
		);

		GameObject::Render(hdc);
	}
}