#pragma once
#include "yaResource.h"

namespace ya
{
	class Sound : public Resource
	{
	public:
		Sound();
		virtual ~Sound();

		int Load(const wchar_t* strPath);

		void Play(bool bIsLoop = false);						// 일반재생

		void PlayBGM(bool bIsLoop = false);						// BGM으로 재생

		void Stop(bool bIsReset = false);

		void SetVolume(float volume);							// 불륨범위 (0 ~ 100)

		void SetPosition(float position);						// 음악파일 위치 조정 0 ~ 100 사이


	private:
		bool loadWaveSound(const std::wstring& strPath);
		int GetDecibel(float volume);

	private:
		LPDIRECTSOUNDBUFFER mpSoundBuffer;
		DSBUFFERDESC mBufferInfoDesc;
		int mVolume;

	};
}

