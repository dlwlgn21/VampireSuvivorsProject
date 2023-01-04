#include "yaGameOverHUDPanel.h"
#include "yaUIManager.h"
#include "yaInput.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaTime.h"
#include "yaSceneManager.h"

namespace ya
{
	GameOverHUDPanel::GameOverHUDPanel()
		: Panel(eUIType::GAME_OVER)
		, mImgWidth(0)
		, mImgHeight(0)
		, mTransparencyTimer(0)
		, mbIsPopup(false)
	{
		mpImage = Resources::Load<Image>(L"GameOverScreen", L"Resources\\Image\\GameOverScreen.bmp");
		assert(mpImage != nullptr);
		mPos = Vector2(0.0f, 0.0f);
		mbIsFullScreen = true;
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mBlendFunc.SourceConstantAlpha = 0;
	}
	void GameOverHUDPanel::OnInitialize()
	{
		mTransparencyTimer = 0;
		mbIsPopup = false;
		Time::Stop();
	}
	void GameOverHUDPanel::OnActive()
	{
	}
	void GameOverHUDPanel::OnInactive()
	{
	}
	void GameOverHUDPanel::OnTick()
	{
		if (!mbIsPopup)
		{
			if (IS_KEY_DOWN(eKeyCode::ESC) || IS_KEY_DOWN(eKeyCode::ENTER))
			{
				UIManager::Pop(eUIType::GAME_OVER);
				SceneManager::ChangeSecne(eSceneType::RESULT_SCENE);
				mbIsPopup = true;
			}
		}
		mTransparencyTimer += 1;
		if (mTransparencyTimer > 127)
		{
			mBlendFunc.SourceConstantAlpha = static_cast<BYTE>(128);
			return;
		}
		mBlendFunc.SourceConstantAlpha = static_cast<BYTE>(mTransparencyTimer);

	}
	void GameOverHUDPanel::OnRender(HDC hdc)
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
	void GameOverHUDPanel::OnUIClear()
	{
		Time::Resume();
	}
}