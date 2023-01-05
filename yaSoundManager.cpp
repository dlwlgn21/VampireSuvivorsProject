#include "yaSoundManager.h"
#include "yaApplication.h"
#include "yaSound.h";
#include "yaResources.h"

namespace ya
{
	LPDIRECTSOUND8 SoundManager::mSoundDevice;

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

		return true;
	}
	Sound* SoundManager::LoadSound(const std::wstring& key, const std::wstring& path)
	{
		Sound* pSound = new Sound();
		pSound->Load();
		return nullptr;
	}

	Sound* SoundManager::GetSound(const std::wstring& key)
	{
		return nullptr;
	}

}