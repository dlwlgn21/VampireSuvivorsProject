#include "yaCharacterSelectionPanel.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaSelectionMenuIcon.h"
#include "yaUIAnimObject.h"
#include "yaUIManager.h"

namespace ya
{

	CharacterSelectionPanel::CharacterSelectionPanel(eUIType type)
		: Panel(eUIType::CHARACTER_SELECTION)
		, mbIsEntered(false)
	{
	}
	void CharacterSelectionPanel::OnInitialize()
	{
	}
	void CharacterSelectionPanel::OnActive()
	{
	}
	void CharacterSelectionPanel::OnInactive()
	{
	}
	void CharacterSelectionPanel::OnTick()
	{
		if (IS_KEY_UP(eKeyCode::ESC))
		{
			UIManager::Pop(eUIType::CHARACTER_SELECTION);
			UIManager::Push(eUIType::START_MENU_SELECTION);
		}
		if (IS_KEY_DOWN(eKeyCode::ENTER) || IS_KEY_DOWN(eKeyCode::SPACE))
		{
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
	void CharacterSelectionPanel::OnUIClear()
	{
	}
}