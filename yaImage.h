#pragma once
#include "yaResource.h"

namespace ya
{
	class Image : public Resource
	{
	public:
		Image();
		~Image();
		HRESULT Load(const std::wstring& path) override;

		inline HDC GetDC() { return mHdc; }
		inline UINT GetWidth() { return mWidth; }
		inline UINT GetHeight() { return mHeight; }

		static Image* Create(const std::wstring& key, UINT width, UINT height);

		Pixel GetPixel(int x, int y);
		void SetPixel(int x, int y, Pixel pixel);

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}

