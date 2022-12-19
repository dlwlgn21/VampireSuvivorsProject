#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class Image;
	class UIBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			// 함수처럼 사용하기 위해서 연산자 오버라이딩
			void operator()()
			{
				if (mEvent != nullptr) { mEvent(); }
			}
			std::function<void()> mEvent;
		};

		UIBase(eUIType type);
		virtual ~UIBase();

		void Initialize();					// UI가 로드되었을 때, 호출하는 초기화 함수
		void Active();						// UI가 활성화 되면, 호출하는 함수
		void Inactive();					// UI가 비활성화 되면, 호출하는 함수
		
		void Tick();
		void Render(HDC hdc);

		void UIClear();						// UI가 사라질 떄 호출되는 함수


		void LoadUIImage(const std::wstring& key, const std::wstring& path);
		void AddUIChild(UIBase* pUIBase);

		__forceinline eUIType GetType() { return mUIType; }
		__forceinline bool GetIsFullScreen() { return mbIsFullScreen; }
		__forceinline void SetIsFullScreen(bool isFullScreen) { mbIsFullScreen = isFullScreen; }
		__forceinline void SetParent(UIBase* parent) { assert(parent != nullptr); mParent = parent; }
		__forceinline void SetPos(Vector2 pos) { mPos = pos; }
		__forceinline Vector2 GetPos() { return mPos; }
		__forceinline void SetSize(Vector2 size) { mSize = size; }
		__forceinline Vector2 GetSize() { return mSize; }
		__forceinline const std::vector<UIBase*>& GetChild() const { return mChilds; }
		
	protected:
		virtual void OnInitialize()	= 0;
		virtual void OnActive()	= 0;
		virtual void OnInactive() = 0;
		virtual void OnTick() = 0;
		virtual void OnRender(HDC hdc) = 0;
		virtual void OnUIClear() = 0;

	protected:
		UIBase* mParent;
		eUIType mUIType;
		bool mbIsFullScreen;
		bool mbIsEnable;
		Image* mpImage;

		Vector2 mPos;
		Vector2 mSize;
		Vector2 mScreenPos;
		std::vector<UIBase*> mChilds;
	};
}

