#include "yaButtonImageObject.h"
#include "yaImage.h"
#include "yaResources.h"

namespace ya
{
	ButtonImageObject::ButtonImageObject(const std::wstring& key, const std::wstring& path)
		: GameObject()
		, mpImage(Resources::Load<Image>(key, path))
		, mbIsSelected(false)
	{
		assert(mpImage != nullptr);
	}
}