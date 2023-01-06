#pragma once
#include "Common.h"

namespace ya
{
	class Sound;
	class SoundManager
	{
	public:
		static SoundManager& GetInstance()
		{
			static SoundManager instance;
			return instance;
		}

		bool Initialize();
		LPDIRECTSOUND8 GetDevice() { return mSoundDevice; }

		Sound* LoadSound(const std::wstring& key, const std::wstring& path);
		Sound* GetSound(const std::wstring& key);
	
	private:
		SoundManager() 
			: mSoundDevice(NULL) 
			, TITLE_BGM_KEY(L"TitleBGM")
			, PLAYSCENE_BGM_KEY(L"PlaySceneBGM")
			, LEVEL_UP_1_KEY(L"LevelUpSound1Key")
			, LEVEL_UP_2_KEY(L"LevelUpSound2Key")
			, ENEMY_HITTED_KEY(L"EnemyHittedSoundKey")
			, GAME_OVER_KEY(L"GameOverSoundKey")
			, SHOOT_KEY(L"PlayerShootSoundKey")
			, PASUED_IN_KEY(L"PasuedInSoundKey")
			, PASUED_OUT_KEY(L"PasuedOutSoundKey")
			, GEM_KEY(L"ExpGemSoundKey")
			, MENU_SELECT_1_KEY(L"MenuSelectSound1key")
			, MENU_SELECT_2_KEY(L"MenuSelectSound2key")
			, MENU_SELECT_3_KEY(L"MenuSelectSound3key")
			, MENU_SELECT_4_KEY(L"MenuSelectSound4key")
			, PLAYER_HITTED_KEY(L"PlayerHittedSoundKey")
		{}
		~SoundManager() = default;

		void loadAllSound();
	public:
		const std::wstring TITLE_BGM_KEY;
		const std::wstring PLAYSCENE_BGM_KEY;
		const std::wstring LEVEL_UP_1_KEY;
		const std::wstring LEVEL_UP_2_KEY;
		const std::wstring ENEMY_HITTED_KEY;
		const std::wstring GAME_OVER_KEY;
		const std::wstring SHOOT_KEY;
		const std::wstring PASUED_IN_KEY;
		const std::wstring PASUED_OUT_KEY;
		const std::wstring GEM_KEY;
		const std::wstring MENU_SELECT_1_KEY;
		const std::wstring MENU_SELECT_2_KEY;
		const std::wstring MENU_SELECT_3_KEY;
		const std::wstring MENU_SELECT_4_KEY;
		const std::wstring PLAYER_HITTED_KEY;
		
	private:
		LPDIRECTSOUND8 mSoundDevice;
		
	};
}
