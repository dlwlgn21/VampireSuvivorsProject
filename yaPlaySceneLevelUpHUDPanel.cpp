#include "yaPlaySceneLevelUpHUDPanel.h"
#include "yaUIManager.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaUIAnimObject.h"
#include "yaLevelUpArrow.h"

namespace ya
{
	PlaySceneLevelUpHUDPanel::PlaySceneLevelUpHUDPanel()
		: Panel(eUIType::PLAY_LEVEL_UP)
		, mpArrow(nullptr)
		, mImgWidth(0)
		, mImgHeight(0)
		, M_TOP_POS(347)
		, M_MID_POS(521)
		, M_BOT_POS(695)
	{
		mpImage = Resources::Load<Image>(L"LevelUpPanel", L"Resources\\Image\\LevelUpPanel.bmp");
		assert(mpImage != nullptr);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mPos = Vector2(SCREEN_WIDTH / 2.0f - mImgWidth / 2.0f, BLACK_BAR_HEIGHT);
		mbIsFullScreen = true;
	}
	void PlaySceneLevelUpHUDPanel::OnInitialize()
	{
	}
	void PlaySceneLevelUpHUDPanel::OnActive()
	{
	}
	void PlaySceneLevelUpHUDPanel::OnInactive()
	{
	}
	void PlaySceneLevelUpHUDPanel::OnTick()
	{
		if (IS_KEY_DOWN(eKeyCode::ENTER) || IS_KEY_DOWN(eKeyCode::SPACE))
		{
			int pos = static_cast<int>(mpArrow->GetPos().y);
			if (pos == M_TOP_POS)
			{
			}
			else if (pos == M_MID_POS)
			{
			}
			else
			{
			}
			UIManager::Pop(eUIType::PLAY_LEVEL_UP);
			UIManager::Push(eUIType::PLAY_INFO_HUD);
		}
	}
	void PlaySceneLevelUpHUDPanel::OnRender(HDC hdc)
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
	void PlaySceneLevelUpHUDPanel::OnUIClear()
	{
	}
	void PlaySceneLevelUpHUDPanel::SetArrow(LevelUpArrow* pArrow)
	{
		assert(pArrow != nullptr);
		mpArrow = pArrow;
	}
}