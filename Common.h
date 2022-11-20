#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <bitset>
#include <memory>
#include <functional>
#include <filesystem>

#include "framework.h"
#include "Maths.h"
#include "def.h"

// 렌더링 라이브러리
#pragma comment(lib, "Msimg32.lib")

// 사운드 라이브러리
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

struct Pixel
{
	BYTE R;
	BYTE G;
	BYTE B;
	BYTE A;

	Pixel(BYTE r, BYTE g, BYTE b, BYTE a)
		: R(r), G(g), B(b), A(a)
	{
	}
};

struct WindowData
{
	// RenderTarget
	HWND hwnd;
	HDC hdc;

	// BITMAP
	HBITMAP backTexture;
	HDC backBuffer;

	UINT height;
	UINT width;
	void Clear()
	{
		HWND hwnd = nullptr;
		HDC hdc = nullptr;
		height = 0;
		width = 0;
	}
};


struct Pen
{
public:
	Pen(HDC hdc)
		: mHdc(hdc)
		, mCurrPen(NULL)
		, mPrevPen(NULL)
	{
	}
	Pen(HDC hdc, HPEN pen)
		: mHdc(hdc)
		, mCurrPen(pen)
		, mPrevPen(NULL)
	{
		mPrevPen = static_cast<HPEN>(SelectObject(mHdc, mCurrPen));
	}
	~Pen()
	{
		SelectObject(mHdc, mPrevPen);
		DeleteObject(mCurrPen);
	}

	HPEN GetCurrPen() { return mCurrPen; }
	void SetPen(HPEN pen)
	{
		mPrevPen = static_cast<HPEN>(SelectObject(mHdc, pen));
	}

private:
	HDC mHdc;
	HPEN mCurrPen;
	HPEN mPrevPen;
};

struct Brush
{
public:
	Brush(HDC hdc, HBRUSH brush)
		: mHdc(hdc)
		, mCurrBrush(brush)
		, mPrevBrush(NULL)
	{
		mPrevBrush = static_cast<HBRUSH>(SelectObject(mHdc, mCurrBrush));
	}
	~Brush()
	{
		SelectObject(mHdc, mPrevBrush);
		DeleteObject(mCurrBrush);
	}
	HBRUSH GetCurrBrush() { return mCurrBrush; }

private:
	HDC mHdc;
	HBRUSH mCurrBrush;
	HBRUSH mPrevBrush;
};