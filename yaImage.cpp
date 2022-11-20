#include <cassert>
#include "yaImage.h"
#include "yaApplication.h"
#include "yaResources.h"

namespace ya
{
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}
	Image::~Image()
	{
		ReleaseDC(Application::GetInstance().GetWindowData().hwnd, mHdc);
	}
	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = static_cast<HBITMAP>(LoadImageW(
			nullptr,
			path.c_str(),
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION
		));

		if (mBitmap == nullptr) { assert(false); return E_FAIL; }

		BITMAP bitInfo = {};
		int res = GetObject(mBitmap, sizeof(BITMAP), &bitInfo);
		if (res == FALSE) { assert(false); return E_FAIL; };

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP prevBitmap = static_cast<HBITMAP>(SelectObject(mHdc, mBitmap));
		DeleteObject(prevBitmap);

		return S_OK;
	}
	Image* Image::Create(const std::wstring& key, UINT width, UINT height)
	{
		Image* image = Resources::Find<Image>(key);
		if (image != nullptr)
		{
			assert(false);
			MessageBox(nullptr, L"NEVER ENTER THIS STATEMENT", L"DUPLICATED_IMAGE", MB_OK);
			return nullptr;
		}

		image = new Image();
		HDC mainHDC = Application::GetInstance().GetHDC();
		image->mBitmap = CreateCompatibleBitmap(mainHDC, width, height);
		if (image->mBitmap == NULL) { assert(false);  return nullptr; }
		image->mHdc = CreateCompatibleDC(mainHDC);
		if (image->mHdc == NULL) { assert(false);  return nullptr; }

		// ���� ������ ��Ʈ�ʰ� DC�� ���� ������ �־�� ��.
		HBITMAP defaultBitmap = static_cast<HBITMAP>(SelectObject(image->mHdc, image->mBitmap));
		DeleteObject(defaultBitmap);

		// ��Ʈ�� ���� Ȯ��
		BITMAP bitmap = {};
		GetObject(image->mBitmap, sizeof(BITMAP), &bitmap);

		image->mWidth = bitmap.bmWidth;
		image->mHeight = bitmap.bmHeight;

		image->SetKey(key);
		Resources::Insert<Image>(key, image);

		return image;
	}
	Pixel Image::GetPixel(int x, int y)
	{
		// ��Ʈ�� ��ǥ��� �����ϴ��� 0,0 ��.
		y = mHeight - (y + 1);					// Bitmap�� ��������ǥ��ʹ� �޸� �ؿ������� �ö󰡱� ������ ���� ������ ��. 
		Pixel* pixel = reinterpret_cast<Pixel*>(mBitmap);
		pixel += (mWidth * y) + x;

		return *pixel;
	}
	void Image::SetPixel(int x, int y, Pixel pixel)
	{
		// ��Ʈ�� ��ǥ��� �����ϴ��� 0,0 ��.
		y = mHeight - (y + 1);					// Bitmap�� ��������ǥ��ʹ� �޸� �ؿ������� �ö󰡱� ������ ���� ������ ��. 
		Pixel* bitPixel = reinterpret_cast<Pixel*>(mBitmap);
		bitPixel += (mWidth * y) + x;
		pixel = *bitPixel;

	}
}