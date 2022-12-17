#include "yaPlayScenePausedHUDPanel.h"
#include "yaUIManager.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaUIAnimObject.h"

namespace ya
{
	PlayScenePausedHUDPanel::PlayScenePausedHUDPanel()
		: Panel(eUIType::PLAY_PAUSED)
		, mImgWidth(0)
		, mImgHeight(0)
		, mpButtons{}
	{
		mpImage = Resources::Load<Image>(L"BlackMask", L"Resources\\Image\\BlackMask.bmp");
		assert(mpImage != nullptr);
		mSize = Vector2(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));
		mPos = Vector2(ACTUAL_GAME_SCREEN_X_DIFF, 0.0f);
		mbIsFullScreen = true;
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mBlendFunc.SourceConstantAlpha = 128;
		for (UINT i = 0; i < static_cast<UINT>(ePauseButton::COUNT); ++i)
		{
			mpButtons[i] = nullptr;
		}
	}
	void PlayScenePausedHUDPanel::OnInitialize()
	{
	}
	void PlayScenePausedHUDPanel::OnActive()
	{
	}
	void PlayScenePausedHUDPanel::OnInactive()
	{
	}
	void PlayScenePausedHUDPanel::OnTick()
	{
		if (IS_KEY_DOWN(eKeyCode::W) || IS_KEY_DOWN(eKeyCode::UP))
		{
			if (mpButtons[static_cast<UINT>(ePauseButton::EXIT)]->IsSelected())
			{ 
				mpButtons[static_cast<UINT>(ePauseButton::CONTINUE)]->SetIsSelected(true); 
				mpButtons[static_cast<UINT>(ePauseButton::EXIT)]->SetIsSelected(false); 
			}
		}
		else if (IS_KEY_DOWN(eKeyCode::S) || IS_KEY_DOWN(eKeyCode::DOWN))
		{
			if (mpButtons[static_cast<UINT>(ePauseButton::CONTINUE)]->IsSelected())
			{ 
				mpButtons[static_cast<UINT>(ePauseButton::EXIT)]->SetIsSelected(true); 
				mpButtons[static_cast<UINT>(ePauseButton::CONTINUE)]->SetIsSelected(false);
			}
		}
		else if (IS_KEY_DOWN(eKeyCode::ENTER) || IS_KEY_DOWN(eKeyCode::SPACE))
		{
			if (mpButtons[static_cast<UINT>(ePauseButton::CONTINUE)]->IsSelected())
				{ mpButtons[static_cast<UINT>(ePauseButton::CONTINUE)]->ButtonClicked(); }
			else
				{ mpButtons[static_cast<UINT>(ePauseButton::EXIT)]->ButtonClicked(); }
		}
	}
	void PlayScenePausedHUDPanel::OnRender(HDC hdc)
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
	}
	void PlayScenePausedHUDPanel::OnUIClear()
	{
	}
	void PlayScenePausedHUDPanel::SetButtonPtrs()
	{
		assert(!mChilds.empty());
		mpButtons[static_cast<UINT>(ePauseButton::CONTINUE)] = static_cast<UIAnimObject*>(mChilds[0]);
		mpButtons[static_cast<UINT>(ePauseButton::EXIT)] = static_cast<UIAnimObject*>(mChilds[1]);
	}
}