#define MAX_TRANSPARENCY_VALUE (255)
#include "yaGameOverExitHUD.h"
#include "yaUIManager.h"
#include "yaInput.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaTime.h"
#include "yaSceneManager.h"

namespace ya
{
	GameOverExitHUD::GameOverExitHUD()
		: Panel(eUIType::GAME_OVER)
		, mImgWidth(0)
		, mImgHeight(0)
		, mTransparencyTimer(0)
	{
		mpImage = Resources::Load<Image>(L"GameOverExit", L"Resources\\Image\\GameOverExitButton.bmp");
		assert(mpImage != nullptr);
		mbIsFullScreen = true;
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mPos = Vector2((SCREEN_WIDTH / 2.0f) - (mImgWidth / 2.0f), SCREEN_HEIGHT / 2.0f);
		mBlendFunc.SourceConstantAlpha = 0;
	}
	void GameOverExitHUD::OnInitialize()
	{
		mTransparencyTimer = 0;
		Time::Stop();
	}
	void GameOverExitHUD::OnActive()
	{
	}
	void GameOverExitHUD::OnInactive()
	{
	}
	void GameOverExitHUD::OnTick()
	{
		mTransparencyTimer += 1;
		if (mTransparencyTimer >= MAX_TRANSPARENCY_VALUE)
		{
			mBlendFunc.SourceConstantAlpha = static_cast<BYTE>(MAX_TRANSPARENCY_VALUE);
			return;
		}
		mBlendFunc.SourceConstantAlpha = static_cast<BYTE>(mTransparencyTimer);
	}
	void GameOverExitHUD::OnRender(HDC hdc)
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
	void GameOverExitHUD::OnUIClear()
	{
		Time::Resume();
	}
}
