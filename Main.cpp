// VampireSuvivorsProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <cassert>
#include "framework.h"
#include "VampireSuvivorsProject.h"
#include "yaApplication.h"


#define MAX_LOADSTRING (100)

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
LPCWSTR gAtlasWindowClassName;
// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, WNDPROC wndProc, LPCWSTR windowClassName);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    AtlasWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

ya::Application& app = ya::Application::GetInstance();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(2167);


    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VAMPIRESUVIVORSPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, WndProc, szWindowClass);     // MainWindow

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VAMPIRESUVIVORSPROJECT));

    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message) { break; }

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            app.Tick();
        }
    }

    if (WM_QUIT == msg.message)
    {
        // 메모리 해제작업
        app.Release();
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance, WNDPROC wndProc, LPCWSTR windowClassName)
{
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = wndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_VAMPIRESUVIVORSPROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_VAMPIRESUVIVORSPROJECT);
    wcex.lpszClassName = windowClassName;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;


    WindowData windowData = {};
    windowData.width = 1920;
    windowData.height = 1080;

    HWND hWnd = CreateWindowW(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        0,
        CW_USEDEFAULT,
        0,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );
    if (hWnd == NULL)
    {
        assert(false);
        return FALSE;
    }
    windowData.hwnd = hWnd;
    windowData.hdc = nullptr;

    // New Part
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
    if (!GetMonitorInfo(hMonitor, &monitorInfo))
    {
        assert(false);
    }
    hWnd = CreateWindowW(
        szWindowClass,
        szTitle,
        WS_POPUP | WS_VISIBLE,
        monitorInfo.rcMonitor.left,
        monitorInfo.rcMonitor.top,
        monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
        monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    // NewPart
    windowData.hwnd = hWnd;
    windowData.hdc = nullptr;

    SetWindowPos(hWnd, nullptr, 0, 0, windowData.width, windowData.height, 0);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    app.Initialize(windowData);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        //SetTimer(hWnd, 0, 1, nullptr);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        //HBRUSH hClearBrush = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
        //HBRUSH hPrevClearBrush = static_cast<HBRUSH>(SelectObject(hdc, hClearBrush));

        //Rectangle(hdc, 0, 0, 1920, 1080);
        //SelectObject(hdc, hPrevClearBrush);
        EndPaint(hWnd, &ps);

    }
    break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
