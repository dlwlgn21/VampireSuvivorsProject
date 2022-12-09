#include "yaStageSelectionPanel.h"
#include "yaSelectionMenuIcon.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaUIAnimObject.h"
#include "yaUIManager.h"
#include "yaSceneManager.h"

namespace ya
{
	StageSelectionPanel::StageSelectionPanel()
		: Panel(eUIType::STAGE_SELECTION)
		, mbIsFirstEntered(true)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"StageSelectionPanel", L"Resources\\Image\\StageSelectionPanel.bmp");
		assert(mpImage != nullptr);

		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mbIsFullScreen = true;
	}
	void StageSelectionPanel::OnInitialize()
	{
	}
	void StageSelectionPanel::OnActive()
	{
	}
	void StageSelectionPanel::OnInactive()
	{
	}
	void StageSelectionPanel::OnTick()
	{
		if (IS_KEY_DOWN(eKeyCode::ESC))
		{
			UIManager::Pop(eUIType::STAGE_SELECTION);
			UIManager::Push(eUIType::START_MENU_SELECTION);
		}
		if (IS_KEY_DOWN(eKeyCode::ENTER) || IS_KEY_DOWN(eKeyCode::SPACE))
		{
			if (static_cast<UIAnimObject*>(mChilds[1])->IsSelected())
			{
				UIManager::Pop(eUIType::STAGE_SELECTION);
				SceneManager::ChangeSecne(eSceneType::PLAY_SCENE);
				UIManager::Push(eUIType::PLAY_INFO_HUD);
			}
			assert(mChilds.size() != 0);
			assert(mChilds.size() == 2);
			if (mbIsFirstEntered)
			{
				mbIsFirstEntered = false;
			}
			else
			{
				static_cast<SelectionMenuIcon*>(mChilds[0])->ChangeRenderImage();
				static_cast<UIAnimObject*>(mChilds[1])->SetIsSelected(true);
			}
		}
	}
	void StageSelectionPanel::OnRender(HDC hdc)
	{
		assert(mpImage != nullptr);

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
	void StageSelectionPanel::OnUIClear()
	{
	}
}