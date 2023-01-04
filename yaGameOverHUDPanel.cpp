#define MAX_TRANSPARENCY_VALUE (128)
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
		, mTransparencyTimer(0.0f)
	{
		mpImage = Resources::Load<Image>(L"GameOverScreen", L"Resources\\Image\\GameOverScreen.bmp");
		assert(mpImage != nullptr);
		mSize = Vector2(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));
		mPos = Vector2(0.0f, 0.0f);
		mbIsFullScreen = true;
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mBlendFunc.SourceConstantAlpha = 0;
	}
	void GameOverHUDPanel::OnInitialize()
	{
		mTransparencyTimer = 0.0f;
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
		if (IS_KEY_DOWN(eKeyCode::ESC) || IS_KEY_DOWN(eKeyCode::ENTER))
		{
			UIManager::Pop(eUIType::GAME_OVER);
			//UIManager::Push(eUIType::PLAY_PAUSED);
		}
		mTransparencyTimer += Time::DeltaTime() * 10;
		if (mTransparencyTimer > 127)
		{
			mBlendFunc.SourceConstantAlpha = static_cast<BYTE>(MAX_TRANSPARENCY_VALUE);
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