#pragma once
#include "yaComponent.h"

namespace ya
{
	class Image;
	class PlayerCustomAnimator;

	class PlayerCustomAnimation final : public Component
	{
		struct PlayerSprite
		{
			Vector2 LeftTop;
			Vector2 Size;
			Vector2 Offset;
			PlayerSprite()
				: LeftTop(Vector2::ZERO)
				, Size(Vector2::ZERO)
				, Offset(Vector2::ZERO)
			{}
		};

	public:
		PlayerCustomAnimation(float minAnimInterval);
		virtual ~PlayerCustomAnimation() = default;

		void Tick() override;
		void Render(HDC hdc) override;

		void Create(
			Image* pImage, Vector2 leftTop,
			Vector2 size, Vector2 offset,
			UINT spriteCount);

		__forceinline void SetScale(Vector2 scale) { mScale = scale; }
		__forceinline void SetAnimator(PlayerCustomAnimator* animator) { mpAnimator = animator; };

	private:
		Image* mpImage;
		PlayerCustomAnimator* mpAnimator;
		std::vector<PlayerSprite> mSpriteSheet;
		UINT mCurrSpriteIdx;
		BLENDFUNCTION mFunc;
		float mMinAnimInterval;
		float mIntervalCounter;
		float mXAfterImageDiff;
		float mYAfterImageDiff;
		Vector2 mScale;
		bool mbIsLeftKeyPressing;
		bool mbIsRightKeyPressing;
		bool mbIsUpKeyPressing;
		bool mbIsDownKeyPressing;
	};
}

