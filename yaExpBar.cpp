#include "yaExpBar.h"
#include "yaPlayer.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaApplication.h"

namespace ya 
{
	ExpBar::ExpBar()
		: HUD(eUIType::PLAY_INFO_HUD)
		, mImgWidth(0)
		, mImgHeight(0)
		, mAmountBarWidth(0)
		, mAmountBarHeight(0)
		, mpPlayer(nullptr)
		, mHwnd(Application::GetInstance().GetWindowData().hwnd)
	{
		mpImage = Resources::Load<Image>(L"EXPBar", L"Resources\\Image\\EXPBar.bmp");
		assert(mpImage != nullptr);
		mpExpAmountBarImage = Resources::Load<Image>(L"EXPAmountBar", L"Resources\\Image\\EXPAmountBar.bmp");
		assert(mpExpAmountBarImage != nullptr);
		mPos = Vector2(static_cast<float>(BLACK_BAR_X_DIFF), 0.0f);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mAmountBarWidth = mpExpAmountBarImage->GetWidth();
		mAmountBarHeight = mpExpAmountBarImage->GetHeight();

		mFont.lfHeight = 30;
		mFont.lfWidth = 0;
		mFont.lfEscapement = 0;
		mFont.lfOrientation = 0;
		mFont.lfItalic = 0;
		mFont.lfUnderline = 0;
		mFont.lfStrikeOut = 0;
		mFont.lfCharSet = ARABIC_CHARSET;
		mFont.lfOutPrecision = 0;
		mFont.lfClipPrecision = 0;
		mFont.lfQuality = 0;
		mFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		lstrcpy(mFont.lfFaceName, L"Tekton Pro");
	}
	void ExpBar::OnInitialize()
	{
	}
	void ExpBar::OnActive()
	{
	}
	void ExpBar::OnInactive()
	{
	}
	void ExpBar::OnTick()
	{
	}
	void ExpBar::OnRender(HDC hdc)
	{
		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x),
			static_cast<int>(mScreenPos.y),
			mImgWidth,
			mImgHeight,

			mpImage->GetDC(),
			0,
			0,
			mImgWidth,
			mImgHeight,
			mBlendFunc
		);

		assert(mpPlayer != nullptr);
		float xRatio = mpPlayer->GetExp() / 100.0f;
		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x + 9),
			static_cast<int>(mScreenPos.y + 9),
			static_cast<int>(mAmountBarWidth * xRatio),
			mAmountBarHeight,

			mpExpAmountBarImage->GetDC(),
			0,
			0,
			mAmountBarWidth,
			mAmountBarHeight,
			mBlendFunc
		);


		wchar_t buffer[BUFFER_LENGTH];
		swprintf_s(buffer, BUFFER_LENGTH, L"Level : %d", mpPlayer->GetLevel());
		int len = lstrlenW(buffer);

		HFONT hFont = CreateFontIndirect(&mFont);
		HFONT hOldFont;
		hOldFont = (HFONT)SelectObject(hdc, hFont);

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOutW(hdc, SCREEN_WIDTH / 2 + 680, 5, buffer, len);

		SelectObject(hdc, hOldFont);
		DeleteObject(hFont);
		ReleaseDC(mHwnd, hdc);
	}
	void ExpBar::OnUIClear()
	{
	}
}