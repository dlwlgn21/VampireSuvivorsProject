#include "yaSoundManager.h"
#include "yaApplication.h"
#include "yaSound.h"
#include "yaResources.h"

namespace ya
{
	bool SoundManager::Initialize()
	{
		if (FAILED(DirectSoundCreate8(NULL, &mSoundDevice, NULL)))
		{
			MessageBox(NULL, L"사운드디바이스생성실패", L"SYSTEM ERROR", MB_OK);
			assert(false);
			return false;
		}

		// 사운드 디바이스 협조레벨 설정.
		HWND hWnd = Application::GetInstance().GetWindowData().hwnd;
		if (FAILED(mSoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag값 정리
		{
			MessageBox(NULL, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);\
			assert(false);
			return false;
		}
		loadAllSound();
		return true;
	}
	Sound* SoundManager::LoadSound(const std::wstring& key, const std::wstring& path)
	{
		Sound* retP = Resources::Load<Sound>(key, path);
		assert(retP != nullptr);
		return retP;
	}

	Sound* SoundManager::GetSound(const std::wstring& key)
	{
		Sound* retP = Resources::Find<Sound>(key);
		return retP;
	}

	void SoundManager::loadAllSound()
	{
		Sound* retP = Resources::Load<Sound>(TITLE_BGM_KEY, L"Resources\\Sfx\\sfx_titleIntro.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(PLAYSCENE_BGM_KEY, L"Resources\\Sfx\\bgm_elrond_library.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(LEVEL_UP_1_KEY, L"Resources\\Sfx\\sfx_autoLevel.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(LEVEL_UP_2_KEY, L"Resources\\Sfx\\sfx_levelup.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(ENEMY_HITTED_KEY, L"Resources\\Sfx\\sfx_enemyHit.wav");
		assert(retP != nullptr);		
		retP = Resources::Load<Sound>(GAME_OVER_KEY, L"Resources\\Sfx\\sfx_gameOver.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(SHOOT_KEY, L"Resources\\Sfx\\sfx_projectile.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(PASUED_IN_KEY, L"Resources\\Sfx\\sfx_sounds_pause7_in.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(PASUED_OUT_KEY, L"Resources\\Sfx\\sfx_sounds_pause7_out.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(GEM_KEY, L"Resources\\Sfx\\sfx_gem.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(MENU_SELECT_1_KEY, L"Resources\\Sfx\\step01.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(MENU_SELECT_2_KEY, L"Resources\\Sfx\\step02.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(MENU_SELECT_3_KEY, L"Resources\\Sfx\\step03.wav");
		assert(retP != nullptr);
		retP = Resources::Load<Sound>(MENU_SELECT_4_KEY, L"Resources\\Sfx\\step04.wav");
		assert(retP != nullptr);
	}

}