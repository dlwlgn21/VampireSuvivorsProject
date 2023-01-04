#include "yaResultScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaObject.h"
#include "yaUIManager.h"
#include "yaResultImage.h"
#include "yaScoreManager.h"
#include "yaApplication.h"
#include "yaTime.h"

namespace ya
{
	ResultScene::ResultScene()
		: mSceneType(eSceneType::RESULT_SCENE)
		, mHwnd(Application::GetInstance().GetWindowData().hwnd)
	{
		mFont.lfHeight = 30;
		mFont.lfWidth = 0;
		mFont.lfEscapement = 0;
		mFont.lfOrientation = 0;
		mFont.lfItalic = 0;
		mFont.lfUnderline = 0;
		mFont.lfStrikeOut = 0;
		mFont.lfCharSet = ARABIC_CHARSET;
		mFont.lfOutPrecision = 0;
		mFont.lfClipPrecision = 0;
		mFont.lfQuality = 0;
		mFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		lstrcpy(mFont.lfFaceName, L"Tekton Pro");
	}

	void ResultScene::Initialize()
	{
		ya::object::InstantiateAtAnotherScene<ResultImage>(eColliderLayer::BACKGROUND, L"BGResultImage", L"Resources\\Image\\ResultImage.bmp", GetSceneTpye());
	}
	void ResultScene::Tick()
	{
		Scene::Tick();
		if (IS_KEY_DOWN(eKeyCode::ENTER) || IS_KEY_DOWN(eKeyCode::ESC))
		{
			SceneManager::ChangeSecne(eSceneType::TITLE_SCENE);
		}
	}
	void ResultScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		float suvivorTime = ScoreManager::GetInstance().GetSuvivorTime();
		wchar_t buffer[BUFFER_LENGTH];
		swprintf_s(buffer, BUFFER_LENGTH, L"%d : %d", static_cast<int>(suvivorTime / 60), static_cast<int>(suvivorTime) % 60);
		int len = lstrlenW(buffer);

		HFONT hFont = CreateFontIndirect(&mFont);
		HFONT hOldFont;
		hOldFont = (HFONT)SelectObject(hdc, hFont);

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOutW(hdc, X_POS, INIT_Y_POS, buffer, len);


		swprintf_s(buffer, BUFFER_LENGTH, L"%d", ScoreManager::GetInstance().GetKillCount());
		len = lstrlenW(buffer);
		TextOutW(hdc, X_POS, INIT_Y_POS + Y_DISTANCE, buffer, len);

		swprintf_s(buffer, BUFFER_LENGTH, L"%d", ScoreManager::GetInstance().GetPlayerLevel());
		len = lstrlenW(buffer);
		TextOutW(hdc, X_POS, INIT_Y_POS + (Y_DISTANCE * 2), buffer, len);

		SelectObject(hdc, hOldFont);
		DeleteObject(hFont);
		ReleaseDC(mHwnd, hdc);
	}
	void ResultScene::Enter()
	{
		Scene::Enter();
	}
	void ResultScene::Exit()
	{
		//Scene::Exit();
		ScoreManager::GetInstance().Initialize();
	}
}