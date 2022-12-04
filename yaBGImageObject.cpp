#include <cassert>
#include "yaBGImageObject.h"
#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	BGImageObject::BGImageObject(const std::wstring& key, const std::wstring& path)
		: GameObject()
		, mpImage(Resources::Load<Image>(key, path))
	{
		assert(mpImage != nullptr);
	}
}