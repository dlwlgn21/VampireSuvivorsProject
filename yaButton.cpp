#include "Def.h"
#include "yaButton.h"
#include "yaImage.h"
#include "yaInput.h"

namespace ya
{
	Button::Button(eUIType type)
		: UIBase(type)
		, mbIsMouseOn(false)
	{
		mOnClick = std::bind(&Button::Click, this);
		ZeroMemory(&mBlendFunc, sizeof(BLENDFUNCTION));
		mBlendFunc.BlendOp = AC_SRC_OVER;
		mBlendFunc.BlendFlags = 0;
		mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
		mBlendFunc.SourceConstantAlpha = 255;
	}

	void Button::OnInitialize()
	{
	}

	void Button::OnActive()
	{
	}

	void Button::OnInactive()
	{
	}

	void Button::OnTick()
	{
		char buffer[128];
		Vector2 mousePos = Input::GetMousePos();
		Vector2 size = GetSize();
		mousePos.y -= 30.0f;
		if (mPos.x <= mousePos.x && mousePos.x < mPos.x + size.x &&
			mPos.y <= mousePos.y && mousePos.y < mPos.y + size.y)
			{ mbIsMouseOn = true; }
		else
			{ mbIsMouseOn = false; }

		if (IS_KEY_DOWN(eKeyCode::L_BUTTON) && mbIsMouseOn)
		{ 
			sprintf_s(buffer, "Mouse Pos.x{%3f}, Pos.y{%3f}\n\n", mousePos.x, mousePos.y);
			OutputDebugStringA(buffer);
			mOnClick(); 
		}
		if (IS_KEY_DOWN(eKeyCode::L_BUTTON))
		{
			sprintf_s(buffer, "Mouse Pos.x{%3f}, Pos.y{%3f}\n\n", mousePos.x, mousePos.y);
			OutputDebugStringA(buffer);
			//mOnClick();
		}
	}

	void Button::OnRender(HDC hdc)
	{
		assert(mpImage != nullptr);

		AlphaBlend(
			hdc,
			static_cast<int>(mPos.x),
			static_cast<int>(mPos.y),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),

			mpImage->GetDC(),
			static_cast<int>(0),
			static_cast<int>(0),
			static_cast<int>(mpImage->GetWidth()),
			static_cast<int>(mpImage->GetHeight()),
			mBlendFunc
		);
	}

	void Button::OnUIClear()
	{
	}

	void Button::Click()
	{
		int a = 0;
	}
}