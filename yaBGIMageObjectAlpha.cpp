#include <cassert>
#include "yaBGImageObjectAlpha.h"
#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	BGImageObjectAlpha::BGImageObjectAlpha(const std::wstring& key, const std::wstring& path)
		: GameObject()
		, mpImage(Resources::Load<Image>(key, path))
	{
		assert(mpImage != nullptr);
	}
}