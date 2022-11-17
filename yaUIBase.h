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

		void Initialize();					// UI�� �ε�Ǿ��� ��, ȣ���ϴ� �ʱ�ȭ �Լ�
		void Activate();					// UI�� Ȱ��ȭ �Ǹ�, ȣ���ϴ� �Լ�
		void InActivate();					// UI�� ��Ȱ��ȭ �Ǹ�, ȣ���ϴ� �Լ�
		
		void Tick();
		void Render(HDC hdc);

		void UIClear();						// UI�� ����� �� ȣ��Ǵ� �Լ�

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

