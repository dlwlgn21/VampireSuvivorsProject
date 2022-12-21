#include <cassert>
#include "yaBGImageObject.h"
#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	BGImageObject::BGImageObject(const std::wstring& key, const std::wstring& path)
		: GameObject()
		, mpImage(Resources::Load<Image>(key, path))
		, mBlendFunc({})
		, mImgWidth(static_cast<int>(mpImage->GetWidth()))
		, mImgHeigt(static_cast<int>(mpImage->GetHeight()))
	{
		assert(mpImage != nullptr);
		assert(mImgWidth != 0);
		assert(mImgHeigt != 0);
		mBlendFunc.BlendOp = AC_SRC_OVER;
		mBlendFunc.BlendFlags = 0;
		mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
		mBlendFunc.SourceConstantAlpha = 255;
	}
}