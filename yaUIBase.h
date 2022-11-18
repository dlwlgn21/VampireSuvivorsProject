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
			// �Լ�ó�� ����ϱ� ���ؼ� ������ �������̵�
			void operator()()
			{
				if (mEvent != nullptr) { mEvent(); }
			}
			std::function<void()> mEvent;
		};

		UIBase(eUIType type);
		virtual ~UIBase();



		void Initialize();					// UI�� �ε�Ǿ��� ��, ȣ���ϴ� �ʱ�ȭ �Լ�
		void Activate();					// UI�� Ȱ��ȭ �Ǹ�, ȣ���ϴ� �Լ�
		void InActivate();					// UI�� ��Ȱ��ȭ �Ǹ�, ȣ���ϴ� �Լ�
		
		void Tick();
		void Render(HDC hdc);

		void UIClear();						// UI�� ����� �� ȣ��Ǵ� �Լ�
		eUIType GetType() { return mUIType; }
		bool GetIsFullScreen() { return mbIsFullScreen; }
		void SetIsFullScreen(bool isFullScreen) { mbIsFullScreen = isFullScreen; }
		void SetParent(UIBase* parent) { mParent = parent; }
		void LoadUIImage(const std::wstring& key, const std::wstring& path);
		__forceinline void SetPos(Vector2 pos) { mScreenPos = pos; }
		__forceinline Vector2 GetPos() { return mScreenPos; }
		__forceinline void SetSize(Vector2 size) { mSize = size; }
		__forceinline Vector2 GetSize() { return mSize; }

	protected:
		virtual void OnInitialize()		{};
		virtual void OnActivate()		{};
		virtual void OnInActivate()		{};
		virtual void OnTick()			{};
		virtual void OnRender(HDC hdc)	{};
		virtual void OnUIClear()		{};

	protected:
		UIBase* mParent;
		eUIType mUIType;
		bool mbIsFullScreen;
		bool mbIsEnable;
		Image* mpImage;
		
		Vector2 mScreenPos;

		Vector2 mPos;
		Vector2 mSize;
	};
}

