#include "yaEndingScene.h"
#include "yaBgImageObject.h"
#include "yaToolScene.h"
#include "yaSceneManager.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaApplication.h"

namespace ya
{
	ToolScene::ToolScene()
		: mSceneType(eSceneType::ENDING_SCENE)
		, mpTilePalette(new TilePalette())
	{
	}
	ToolScene::~ToolScene()
	{
		delete mpTilePalette;
	}
	void ToolScene::Initialize()
	{
		//BgImageObject* bg = new BgImageObject(L"");
		//AddGameObject(bg);
		//SceneManager::Initialze();
	}
	void ToolScene::Tick()
	{
		Scene::Tick();
		if (IS_KEY_UP(eKeyCode::N))
		{
			SceneManager::ChangeSecne(eSceneType::LOGO_SCENE);
		}
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		WindowData mainWinData = Application::GetInstance().GetWindowData();
		wchar_t buffer[64];
		swprintf_s(buffer, 64, L"Tool Scene");
		size_t strLen = wcsnlen_s(buffer, 64);
		TextOut(hdc, 10, 30, buffer, strLen);

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 200, 0,));
		HPEN prevPen = static_cast<HPEN>(SelectObject(hdc, greenPen));
		int maxRow = mainWinData.height / TILE_SIZE_X + 1;
		for (int i = 0; i < maxRow; ++i)
		{
			MoveToEx(hdc, 0, TILE_SIZE_X * i, nullptr);
			LineTo(hdc, mainWinData.width, TILE_SIZE_X * i);
		}
		
		int maxCol = mainWinData.width / TILE_SIZE_X + 1;
		for (int i = 0; i < maxCol; ++i)
		{
			MoveToEx(hdc, TILE_SIZE_X * i, 0, nullptr);
			LineTo(hdc, TILE_SIZE_X * i, mainWinData.height);
		}
		SelectObject(hdc, prevPen);
		DeleteObject(greenPen);
	}
	void ToolScene::Enter()
	{
		Scene::Enter();
		Application::GetInstance().SetMenuBar(true);
	}
	void ToolScene::Exit()
	{
		Scene::Exit();
	}
}