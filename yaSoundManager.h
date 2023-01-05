#pragma once
#include "Common.h"

namespace ya
{
	class Sound;
	class SoundManager
	{
	public:
		static bool Initialize();
		static LPDIRECTSOUND8 GetDevice() { return mSoundDevice; }
		static Sound* LoadSound(const std::wstring& key, const std::wstring& path);
		static Sound* GetSound(const std::wstring& key);
	private:
		static LPDIRECTSOUND8 mSoundDevice;
	};
}
