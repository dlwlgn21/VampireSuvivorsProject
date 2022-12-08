#pragma once
#include "yaUIBase.h"

namespace ya
{
	class Image;
	class UIAnimObject : public UIBase
	{
	public:
		struct Sprite
		{
			Vector2 LeftTop;
			Vector2 Size;
			Vector2 Offset;

			Sprite()
				: LeftTop(Vector2::ZERO)
				, Size(Vector2::ZERO)
				, Offset(Vector2::ZERO)
			{
			}
		};
		UIAnimObject(eUIType type);
		UIAnimObject(const UIAnimObject& other) = delete;
		UIAnimObject& operator=(const UIAnimObject& other) = delete;
		virtual ~UIAnimObject() = default;
		__forceinline Vector2 GetAnimSize() { return mAnimSize; }
		__forceinline bool IsSelected() { return mbIsSelected; }
		__forceinline void SetIsSelected(bool isSelected) { mbIsSelected = isSelected; }
		virtual void ButtonClicked() = 0;
	protected:
		void Create(
			Image* pImage, Vector2 size, 
			Vector2 offset, UINT spriteCount, 
			float duration, bool bIsAffectedCamera = true
		);

		void ResetWithoutSpriteIdx();
		__forceinline void SetScale(Vector2 scale) { mScale = scale; }

		virtual void OnInitialize() override;
		virtual void OnActive() override;
		virtual void OnInactive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnUIClear() override;

	protected:
		Image* mpAnimImage;
		Image* mpNonAnimImage;
		Image* mpCurrRenderImage;
		std::vector<Sprite> mSpriteSheet;
		BLENDFUNCTION mBlendFunc;
		UINT mCurrSpriteIdx;
		Vector2 mScale;
		Vector2 mAnimSize;
		float mTimer;
		float mAnimDuration;
		bool mbIsAffectedCamera;
		bool mbIsSelected;
	};
}


