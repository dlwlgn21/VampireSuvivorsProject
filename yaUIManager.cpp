#include "yaUIManager.h"


namespace ya
{

	std::unordered_map<eUIType, UIBase*> UIManager::mUIMap;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UIBase*> UIManager::mUIStack;
	UIBase* UIManager::mpCurrUIBase = nullptr;

	void UIManager::Initialize()					// 여기에서 UI 메모리 할당
	{
		UIBase* pNewUI = new UIBase(eUIType::HP);
		mUIMap.insert(std::make_pair(eUIType::HP, pNewUI));

		pNewUI = new UIBase(eUIType::MP);
		mUIMap.insert(std::make_pair(eUIType::MP, pNewUI));

		pNewUI = new UIBase(eUIType::INVENTORY);
		mUIMap.insert(std::make_pair(eUIType::INVENTORY, pNewUI));

		pNewUI = new UIBase(eUIType::OPTIOIN);
		mUIMap.insert(std::make_pair(eUIType::OPTIOIN, pNewUI));

		pNewUI = new UIBase(eUIType::SHOP);
		mUIMap.insert(std::make_pair(eUIType::SHOP, pNewUI));

	}
	void UIManager::OnLoad(eUIType uiType)
	{
		auto iter = mUIMap.find(uiType);
		if (iter == mUIMap.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}
	void UIManager::OnFail()
	{
	}
	void UIManager::OnComplete(UIBase* pAddedUIType)
	{
	}

	void UIManager::Tick()
	{
		if (mRequestUIQueue.size() > 0)
		{
			// UI 로드 해주어야 함.
			eUIType requestUiType = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			OnLoad(requestUiType);
		}
	}
	void UIManager::Render(HDC hdc)
	{
	}
	void UIManager::Push(eUIType uiType)
	{
		mRequestUIQueue.push(uiType);
	}
	void UIManager::Pop(eUIType uiType)
	{
	}
	void UIManager::Release()
	{
		for (auto iter = mUIMap.begin(); iter != mUIMap.end(); ++iter)
		{
			if (iter->second != nullptr) { delete iter->second; }
		}
		mUIMap.clear();
	}
}