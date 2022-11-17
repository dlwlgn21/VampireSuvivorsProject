#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class UIBase : public Entity
	{
	public:
		UIBase(eUIType type);
		virtual ~UIBase();

		void Initialize();					// UI가 로드되었을 때, 호출하는 초기화 함수
		void Activate();					// UI가 활성화 되면, 호출하는 함수
		void InActivate();					// UI가 비활성화 되면, 호출하는 함수
		
		void Tick();
		void Render(HDC hdc);

		void UIClear();						// UI가 사라질 떄 호출되는 함수

		virtual void OnInitialize() {};
		virtual void OnActivate()	{};
		virtual void OnInActivate() {};
		virtual void OnTick()		{};
		virtual void OnUIClear()	{};

		eUIType GetType() { return mUIType; }
		bool GetIsFullScreen() { return mbIsFullScreen; }
		void SetIsFullScreen(bool isFullScreen) { mbIsFullScreen = isFullScreen; }

	private:
		eUIType mUIType;
		bool mbIsFullScreen;
		bool mbIsEnable;
	};
}

