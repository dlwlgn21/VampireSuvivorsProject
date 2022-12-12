#include "yaPlaySceneHUDPanel.h"
#include "yaHealthBar.h"
#include "yaInput.h"
#include "yaUIManager.h"

namespace ya
{
	PlaySceneHUDPanel::PlaySceneHUDPanel()
		: Panel(eUIType::PLAY_INFO_HUD)
	{
		mSize = Vector2(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));
		mbIsFullScreen = true;
	}
	void PlaySceneHUDPanel::OnInitialize()
	{
	}
	void PlaySceneHUDPanel::OnActive()
	{
	}
	void PlaySceneHUDPanel::OnInactive()
	{
	}
	void PlaySceneHUDPanel::OnTick()
	{
		if (IS_KEY_DOWN(eKeyCode::ESC))
		{
			UIManager::Pop(eUIType::PLAY_INFO_HUD);
			UIManager::Push(eUIType::PLAY_PAUSED);
		}
	}
	void PlaySceneHUDPanel::OnRender(HDC hdc)
	{
	}
	void PlaySceneHUDPanel::OnUIClear()
	{
	}
	void PlaySceneHUDPanel::SetHpBarToPlayer(Player* pPlayer)
	{
		assert(mChilds[0] != nullptr);
		static_cast<HealthBar*>(mChilds[0])->SetPlayer(pPlayer);
	}
}