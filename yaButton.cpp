#include "Def.h"
#include "yaButton.h"
#include "yaImage.h"
#include "yaInput.h"
namespace ya
{
	Button::Button(eUIType type)
		: UIBase(type)
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

	void Button::OnActivate()
	{
	}

	void Button::OnInActivate()
	{
	}

	void Button::OnTick()
	{
		Vector2 mousePos = Input::GetMousePos();
		Vector2 size = GetSize();
		if (mousePos.x >= mScreenPos.x && mousePos.x <= mScreenPos.x + size.x &&
			mousePos.y >= mScreenPos.y && mousePos.y <= mScreenPos.y + size.y)
		{ mbIsMouseOn = true; }
		else
		{ mbIsMouseOn = false; }

		if (IS_KEY_DOWN(eKeyCode::L_BUTTON) && mbIsMouseOn)
		{ mOnClick(); }
	}

	void Button::OnRender(HDC hdc)
	{
		if (mpImage == nullptr) { return; }
		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
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