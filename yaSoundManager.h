#pragma once

namespace ya
{
	class SoundManager final
	{
	public:
		static SoundManager& GetInstance()
		{
			static SoundManager instance;
			return instance;
		}
		SoundManager(const SoundManager& other) = delete;
		SoundManager& operator=(const SoundManager& other) = delete;

	private:
		SoundManager() = default;
		~SoundManager() = default;
	};
}

