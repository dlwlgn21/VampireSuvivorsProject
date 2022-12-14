#include "yaCharacterSelectionPanel.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaSelectionMenuIcon.h"
#include "yaUIAnimObject.h"
#include "yaUIManager.h"
#include "yaSoundManager.h"
#include "yaSound.h"

namespace ya
{

	CharacterSelectionPanel::CharacterSelectionPanel(eUIType type)
		: Panel(eUIType::CHARACTER_SELECTION)
		, mbIsFirstEntered(true)
		, mImgWidth(0)
		, mImgHeight(0)
	{
		mpImage = Resources::Load<Image>(L"CharacterSelectionPanel", L"Resources\\Image\\CharacterSelectionPanelClean.bmp");
		assert(mpImage != nullptr);
		mImgWidth = mpImage->GetWidth();
		mImgHeight = mpImage->GetHeight();
		mSize = Vector2(static_cast<float>(mImgWidth), static_cast<float>(mImgHeight));
		mbIsFullScreen = true;
	}
	void CharacterSelectionPanel::OnInitialize()
	{
		Input::Initialize();
		mbIsFirstEntered = true;
	}
	void CharacterSelectionPanel::OnActive()
	{
	}
	void CharacterSelectionPanel::OnInactive()
	{
	}
	void CharacterSelectionPanel::OnTick()
	{
		if (IS_KEY_DOWN(eKeyCode::ESC))
		{
			SoundManager& sm = SoundManager::GetInstance();
			Sound* pSound = sm.GetSound(sm.PASUED_OUT_KEY);
			pSound->Play(false);
			UIManager::Pop(eUIType::CHARACTER_SELECTION);
			UIManager::Push(eUIType::START_MENU_SELECTION);
		}
		if (IS_KEY_DOWN(eKeyCode::ENTER) || IS_KEY_DOWN(eKeyCode::SPACE))
		{
			if (mbIsFirstEntered)
			{
				mbIsFirstEntered = !mbIsFirstEntered;
				return;
			}
			SoundManager& sm = SoundManager::GetInstance();
			Sound* pSound = sm.GetSound(sm.PASUED_IN_KEY);
			pSound->Play(false);
			if (static_cast<UIAnimObject*>(mChilds[2])->IsSelected())
			{
				UIManager::Pop(eUIType::CHARACTER_SELECTION);
				UIManager::Push(eUIType::STAGE_SELECTION);
				SoundManager& sm = SoundManager::GetInstance();
				Sound* pSound = sm.GetSound(sm.PASUED_OUT_KEY);
				pSound->Play(false);
			}
			assert(mChilds.size() != 0);
			assert(mChilds.size() == 3);
			for (int i = 0; i < mChilds.size() - 1; ++i)
			{
				static_cast<SelectionMenuIcon*>(mChilds[i])->ChangeRenderImage();
			}
			static_cast<UIAnimObject*>(mChilds[2])->SetIsSelected(true);
		}
	}
	void CharacterSelectionPanel::OnRender(HDC hdc)
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
	void CharacterSelectionPanel::OnUIClear()
	{
		Input::Initialize();
	}
}