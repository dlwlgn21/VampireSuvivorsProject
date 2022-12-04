#include <assert.h>
#include "framework.h"
#include "VampireSuvivorsProject.h"
#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResources.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaSoundManager.h"
#include "yaUIManager.h"

namespace ya
{
	Application::~Application()
	{
	}

	void Application::Initialize(WindowData data)
	{
		mWindowData = data;
		mWindowData.hdc = GetDC(data.hwnd);

		initailizeWindow();

		Time::Initialize();
		Input::Initialize();
		UIManager::Initialize();
		SceneManager::Initialze();
		Camera::Initialize();
		//SoundManager::Initialize();
	}

	void Application::InitializeAtalsWindow(WindowData atlasWindowData)
	{
		mAtlasWindowData = atlasWindowData;
		mAtlasWindowData.hdc = GetDC(atlasWindowData.hwnd);
	}

	void Application::initailizeWindow()
	{
		// ��Ʈ�� �ػ󵵸� �����ϱ� ���� ���� ������ ũ�� ���
		RECT rect = { 0,0, static_cast<LONG>(mWindowData.width), static_cast<LONG>(mWindowData.height) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// ������ ũ�� ����
		SetWindowPos(
			mWindowData.hwnd,
			nullptr, 0, 0,
			rect.right - rect.left,
			rect.bottom - rect.top,
			SWP_NOMOVE | SWP_NOZORDER
		);

		ShowWindow(mWindowData.hwnd, true);

		mWindowData.backTexture = CreateCompatibleBitmap(mWindowData.hdc, mWindowData.width, mWindowData.height);

		// BackBuffer �����
		mWindowData.backBuffer = CreateCompatibleDC(mWindowData.hdc);
		HBITMAP defaultBitmap = static_cast<HBITMAP>(SelectObject(mWindowData.backBuffer, mWindowData.backTexture));

		DeleteObject(defaultBitmap);

		// �޸� ���� ���־�� ��.
		mPens[static_cast<UINT>(ePenColor::RED)] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[static_cast<UINT>(ePenColor::GREEN)] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[static_cast<UINT>(ePenColor::BLUE)] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		mBrushes[static_cast<UINT>(eBrushColor::TRANS_PARENT)] = static_cast<HBRUSH>(GetStockObject(HOLLOW_BRUSH));
		mBrushes[static_cast<UINT>(eBrushColor::BLACK)] = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		mBrushes[static_cast<UINT>(eBrushColor::GRAY)] = CreateSolidBrush(RGB(67, 67, 67));
		mBrushes[static_cast<UINT>(eBrushColor::WHITE)] = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	
		mMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_VAMPIRESUVIVORSPROJECT));
	}

	void Application::Tick()
	{
		Time::Tick();
		Input::Tick();

		SceneManager::Tick();
		CollisionManager::Tick();
		UIManager::Tick();
		Camera::Tick();

		HBRUSH hPrevBrush = (HBRUSH)SelectObject(mWindowData.backBuffer, mBrushes[(UINT)eBrushColor::BLACK]);

		// Clear �̳� ������ ����.
		Rectangle(
			mWindowData.backBuffer, -1, -1,
			mWindowData.width + 1, mWindowData.height + 1);
		SelectObject(mWindowData.backBuffer, hPrevBrush);

		SceneManager::Render(mWindowData.backBuffer);
		UIManager::Render(mWindowData.backBuffer);
		Camera::Render(mWindowData.backBuffer);
		Input::Render(mWindowData.backBuffer);
		Time::Render(mWindowData.backBuffer);

		// BitBlt �Լ��� DC���� �̹����� �������ִ� �Լ�
		// ����ۿ� �ִ� ������ �����Ѵ�.
		BitBlt(
			mWindowData.hdc,
			0, 0, mWindowData.width, mWindowData.height,
			mWindowData.backBuffer,						// ��𿡴ٰ� �׸��ų�.
			0, 0,
			SRCCOPY										// ��� �׸��ų�
		);

		// ƽ�� ���� ��� ������ Gameobject ���� 
		SceneManager::DestroyGameobject();
	}

	void Application::SetMenuBar(bool power)
	{
		SetMenu(mWindowData.hwnd, mMenu);				// WinAPI �⺻ ���� �Լ�.
		
		RECT rect = { 0,0, static_cast<LONG>(mWindowData.width), static_cast<LONG>(mWindowData.height) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);

		SetWindowPos(
			mWindowData.hwnd,
			nullptr, 0, 0,
			rect.right - rect.left,
			rect.bottom - rect.top,
			SWP_NOMOVE | SWP_NOZORDER
		);
		ShowWindow(mWindowData.hwnd, true);
	}
	void Application::Release()
	{
		SceneManager::Release();
		ReleaseDC(mWindowData.hwnd, mWindowData.hdc);
		ReleaseDC(mWindowData.hwnd, mWindowData.backBuffer);
		UIManager::Release();
	}
}
