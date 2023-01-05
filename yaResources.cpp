#include "yaResources.h"
namespace ya
{
	std::unordered_map<std::wstring, std::unique_ptr<Resource>> Resources::mResources;
	std::unordered_map<std::wstring, std::unique_ptr<Resource>> Resources::mSoundResources;


	Sound* Resources::LoadSound(const std::wstring& key, const std::wstring& path)
	{
		return nullptr;
	}
	Sound* Resources::FindSound(const std::wstring& key)
	{
		return nullptr;
	}
}