#include "yaSound.h"
#include "yaSoundManager.h"

namespace ya
{
	Sound::Sound()
	{
	}
	Sound::~Sound()
	{
	}
	int Sound::Load(const wchar_t* strPath)
	{
		return 0;
	}
	void Sound::Play(bool bIsLoop)
	{
		// Play 함수의 1번째, 2번째 인자는 0으로 이미 예약되어 있음.
		// 3번째 변수는 사운드를 반복재생 할 것인지 아닌지를 결정한다
		if (bIsLoop)
			{ mpSoundBuffer->Play(0, 0, DSBPLAY_LOOPING); }
		else
			{ mpSoundBuffer->Play(0, 0, 0); }
	}
	void Sound::PlayBGM(bool bIsLoop)
	{
		//SoundManager::GetInstance().RegisterBGM(this);

		// Play 함수의 1번째, 2번째 인자는 0으로 이미 예약되어 있음.
		// 3번째 변수는 사운드를 반복재생 할 것인지 아닌지를 결정한다
		if (bIsLoop)
			{ mpSoundBuffer->Play(0, 0, DSBPLAY_LOOPING); }
		else
			{ mpSoundBuffer->Play(0, 0, 0); }
	}
	void Sound::Stop(bool bIsReset)
	{
		mpSoundBuffer->Stop();
		if (bIsReset)
			{ mpSoundBuffer->SetCurrentPosition(0); }
	}
	void Sound::SetVolume(float volume)
	{
		mVolume = GetDecibel(volume);
		mpSoundBuffer->SetVolume(mVolume);
	}
	void Sound::SetPosition(float position)
	{
		Stop(true);

		DWORD dwBytes = (DWORD)((position / 100.0f) * static_cast<float>(mBufferInfoDesc.dwBufferBytes));
		mpSoundBuffer->SetCurrentPosition(dwBytes);
		Play();
	}
	bool Sound::loadWaveSound(const std::wstring& strPath)
	{
		HMMIO fileHandle;

		std::wstring filePath = strPath;

		// Create File
		fileHandle = mmioOpen((wchar_t*)filePath.c_str(), NULL, MMIO_READ);					// wave 파일을 open
		if (fileHandle == nullptr)
		{
			assert(false);
			return false;
		}

		// Chunk 청크 구조체. 문자열로 색인을 인식해서 WaveFormat 및 버퍼선언정보를 읽어온다.
		MMCKINFO pParent;
		memset(&pParent, 0, sizeof(pParent));
		pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(fileHandle, &pParent, NULL, MMIO_FINDRIFF);

		MMCKINFO pChild;
		memset(&pChild, 0, sizeof(pChild));
		pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(fileHandle, &pChild, &pParent, MMIO_FINDCHUNK);

		WAVEFORMATEX wft;
		memset(&wft, 0, sizeof(wft));
		mmioRead(fileHandle, (char*)&wft, sizeof(wft));

		mmioAscend(fileHandle, &pChild, 0);
		pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(fileHandle, &pChild, &pParent, MMIO_FINDCHUNK);



		memset(&mBufferInfoDesc, 0, sizeof(DSBUFFERDESC));
		mBufferInfoDesc.dwBufferBytes = pChild.cksize;
		mBufferInfoDesc.dwSize = sizeof(DSBUFFERDESC);
		mBufferInfoDesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
		mBufferInfoDesc.lpwfxFormat = &wft;


		// TODO : 나중에 다시 작성해야함. 8분 48초에 있음.
		//if (FAILED( SoundManager::GetInstance().GetSoundDevice().CreateSoundBuffer(&mBufferInfoDesc, mpSoundBuffer, NULL) ))
		//{
			//assert(false);
			//return false;
		//}

		void* pWrite1 = NULL;
		void* pWrite2 = NULL;
		DWORD dwlength1, dwlength2;

		mpSoundBuffer->Lock(
			0, pChild.cksize, 
			&pWrite1, &dwlength1,
			&pWrite2, &dwlength2, 
			0L
		);

		if (pWrite1 > 0)
			{ mmioRead(fileHandle, (char*)pWrite1, dwlength1); }
		if (pWrite2 > 0)
			{ mmioRead(fileHandle, (char*)pWrite2, dwlength2); }

		mpSoundBuffer->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

		mmioClose(fileHandle, 0);

		// 초기음량 절반으로 설정
		SetVolume(50.0f);
		return true;
	}
	int Sound::GetDecibel(float volume)
	{
		// 데시벨이 10 올라가면 실제로는 10배씩 올라간다.

		if (volume > 100.0f)
			{ volume = 100.0f; }
		else if (volume <= 0.0f)
			{ volume = 0.00001f; }

		// 1 ~ 100 사이값을 데시벨 단위로 변경
		int iVolume = (LONG)(-2000.0 * log10(100.0f / volume));

		if (iVolume < -10000)
		{
			iVolume = -10000;
		}
		return iVolume;
	}
}