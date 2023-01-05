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

		void Play(bool bIsLoop = false);						// �Ϲ����

		void PlayBGM(bool bIsLoop = false);						// BGM���� ���

		void Stop(bool bIsReset = false);

		void SetVolume(float volume);							// �ҷ����� (0 ~ 100)

		void SetPosition(float position);						// �������� ��ġ ���� 0 ~ 100 ����


	private:
		bool loadWaveSound(const std::wstring& strPath);
		int GetDecibel(float volume);

	private:
		LPDIRECTSOUNDBUFFER mpSoundBuffer;
		DSBUFFERDESC mBufferInfoDesc;
		int mVolume;

	};
}

