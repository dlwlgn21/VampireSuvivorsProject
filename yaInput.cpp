#include "yaInput.h"
#include "yaApplication.h"

namespace ya
{

	//// Special Key
	//	ENTER, ESC, L_SHIFT, L_ALT, L_CTRL,
	//	SPACE, LEFT, RIGHT, UP, DOWN,
	//	L_BUTTON, R_BUTTON,

	//	// NumPad
	//	NUM_0, NUM_1, NUM_2,
	//	NUM_3, NUM_4, NUM_5,
	//	NUM_6, NUM_7, NUM_8,
	//	NUM_9,

	//	// Num Line
	//	N_0, N_1, N2, N_3, N_4, N5, N_6, N_7, N8, N_9,

	char ASCII[static_cast<char>(eKeyCode::COUNT)] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		static_cast<char>(VK_RETURN), static_cast<char>(VK_ESCAPE), static_cast<char>(VK_LSHIFT), static_cast<char>(VK_LMENU), static_cast<char>(VK_LCONTROL),
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON,

		VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2,
		VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8,
		VK_NUMPAD9,

		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

	};

	Vector2 Input::mMousePos;
	std::vector<Input::Key> Input::mKeys;
	HWND Input::mHwnd = Application::GetInstance().GetWindowData().hwnd;
	void Input::Initialize()
	{
		mKeys.clear();
		mKeys.reserve(128);
		for (int i = 0; i < static_cast<UINT>(eKeyCode::COUNT); ++i)
		{
			Key key;
			key.keyCode = static_cast<eKeyCode>(i);
			key.state = eKeyState::NONE;
			key.bIsPressed = false;
			mKeys.push_back(key);
		}
	}
	void Input::Tick()
	{
		if (GetFocus())
		{
			for (int i = 0; i < static_cast<UINT>(eKeyCode::COUNT); ++i)
			{
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// ���� �����ӿ� ������ �־���.
					if (mKeys[i].bIsPressed)	{ mKeys[i].state = eKeyState::PRESSED; }
					else						{ mKeys[i].state = eKeyState::DOWN; }
					mKeys[i].bIsPressed = true;
				}
				else
				{
					if (mKeys[i].bIsPressed)	{ mKeys[i].state = eKeyState::UP; }
					else						{ mKeys[i].state = eKeyState::NONE; }
					mKeys[i].bIsPressed = false;
				}
			}

			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(mHwnd, &mousePos);
			mMousePos.x = static_cast<float>(mousePos.x);
			mMousePos.y = static_cast<float>(mousePos.y);
			
		}
		else // ��Ŀ���� ����� ��
		{
			for (int i = 0; i < static_cast<UINT>(eKeyCode::COUNT); ++i)
			{
				// ���������� Ű�� ������. UP���� �������.
				if (eKeyState::DOWN == mKeys[i].state || eKeyState::PRESSED == mKeys[i].state) { mKeys[i].state = eKeyState::UP; }
				else if (eKeyState::UP == mKeys[i].state) { mKeys[i].state = eKeyState::NONE; }
				mKeys[i].bIsPressed = false;
			}
		}

	}
	void Input::Render(HDC hdc)
	{
	}
	eKeyState Input::GetKeyState(eKeyCode keyCode)
	{
		return mKeys[static_cast<UINT>(keyCode)].state;
	}
	Vector2 Input::GetMousePos(HWND hwnd)
	{
		Vector2 vMousePos(-1.0f, -1.0f);
		if (GetFocus())
		{
			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(hwnd, &mousePos);
			vMousePos.x = static_cast<float>(mousePos.x);
			vMousePos.y = static_cast<float>(mousePos.y);
			return vMousePos;
		}
		return vMousePos;
	}
}