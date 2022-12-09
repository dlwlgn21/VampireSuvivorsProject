#include "yaStartMenuPanel.h"
#include "yaUIAnimObject.h"
#include "yaInput.h"

namespace ya
{
	StartMenuPanel::StartMenuPanel()
		: Panel(eUIType::START_MENU_SELECTION)
		, mbIsUpKeyDown(false)
		, mbIsCharacterSelectionUIPoped(false)
	{
		mSize = Vector2(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));
		for (UINT i = 0; i < static_cast<UINT>(eStartSelection::COUNT); ++i)
		{
			mpButtonsPtr[i] = nullptr;
		}
		mbIsFullScreen = true;
	}
	void StartMenuPanel::OnInitialize()
	{
		mbIsCharacterSelectionUIPoped = false;
	}
	void StartMenuPanel::OnActive()
	{
		//mbIsFullScreen = true;
		//mbIsCharacterSelectionUIPoped = false;
	}
	void StartMenuPanel::OnInactive()
	{
	}
	void StartMenuPanel::OnTick()
	{
		if (mbIsCharacterSelectionUIPoped)
			{ return; }
		if (IS_KEY_DOWN(eKeyCode::W) || IS_KEY_DOWN(eKeyCode::UP) && !mbIsUpKeyDown)
		{
			if (!mpButtonsPtr[static_cast<UINT>(eStartSelection::EXIT)]->IsSelected())
			{
				mpButtonsPtr[static_cast<UINT>(eStartSelection::START)]->SetIsSelected(false);
				mpButtonsPtr[static_cast<UINT>(eStartSelection::OPTION)]->SetIsSelected(true);
				mbIsUpKeyDown = true;
			}
		}
		else if ((IS_KEY_DOWN(eKeyCode::D) || IS_KEY_DOWN(eKeyCode::RIGHT)) && mbIsUpKeyDown)
		{
			mpButtonsPtr[static_cast<UINT>(eStartSelection::OPTION)]->SetIsSelected(true);
			mpButtonsPtr[static_cast<UINT>(eStartSelection::EXIT)]->SetIsSelected(false);
			mpButtonsPtr[static_cast<UINT>(eStartSelection::START)]->SetIsSelected(false);
		}
		else if ((IS_KEY_DOWN(eKeyCode::A) || IS_KEY_DOWN(eKeyCode::LEFT)) && mbIsUpKeyDown)
		{
			mpButtonsPtr[static_cast<UINT>(eStartSelection::OPTION)]->SetIsSelected(false);
			mpButtonsPtr[static_cast<UINT>(eStartSelection::EXIT)]->SetIsSelected(true);
		}
		else if (IS_KEY_DOWN(eKeyCode::S) || IS_KEY_DOWN(eKeyCode::DOWN))
		{
			mpButtonsPtr[static_cast<UINT>(eStartSelection::START)]->SetIsSelected(true);
			mpButtonsPtr[static_cast<UINT>(eStartSelection::OPTION)]->SetIsSelected(false);
			mpButtonsPtr[static_cast<UINT>(eStartSelection::EXIT)]->SetIsSelected(false);
			mbIsUpKeyDown = false;
		}
		if (IS_KEY_UP(eKeyCode::ENTER) || IS_KEY_UP(eKeyCode::SPACE))
		{
			for (UINT i = 0; i < static_cast<UINT>(eStartSelection::COUNT); ++i)
			{
				if (mpButtonsPtr[i]->IsSelected())
				{
					if (mpButtonsPtr[i] == mpButtonsPtr[static_cast<UINT>(eStartSelection::START)])
					{
						mbIsCharacterSelectionUIPoped = true;
					}
					mpButtonsPtr[i]->ButtonClicked();
				}
			}
		}
	}
	void StartMenuPanel::OnRender(HDC hdc)
	{
	}
	void StartMenuPanel::OnUIClear()
	{
	}
	void StartMenuPanel::SetButtonPtr()
	{
		mpButtonsPtr[static_cast<UINT>(eStartSelection::START)] = static_cast<UIAnimObject*>(mChilds[static_cast<UINT>(eStartSelection::START)]);
		mpButtonsPtr[static_cast<UINT>(eStartSelection::OPTION)] = static_cast<UIAnimObject*>(mChilds[static_cast<UINT>(eStartSelection::OPTION)]);
		mpButtonsPtr[static_cast<UINT>(eStartSelection::EXIT)] = static_cast<UIAnimObject*>(mChilds[static_cast<UINT>(eStartSelection::EXIT)]);

		for (UINT i = 0; i < static_cast<UINT>(eStartSelection::COUNT); ++i)
		{
			assert(mpButtonsPtr[i] != nullptr);
		}
	}
}