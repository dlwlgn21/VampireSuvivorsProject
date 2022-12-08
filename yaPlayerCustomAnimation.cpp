#include "yaPlayerCustomAnimation.h"
#include "yaPlayerCustomAnimator.h"
#include "yaImage.h"
#include "yaTime.h"
#include "yaCamera.h"
#include "yaInput.h"

namespace ya
{
	PlayerCustomAnimation::PlayerCustomAnimation(float minAnimInterval)
		: Component(eComponentType::PLAYER_ANIMATION)
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mCurrSpriteIdx(0)
		, mMinAnimInterval(minAnimInterval)
		, mIntervalCounter(0.0f)
		, mScale(Vector2::ONE)
		, mFunc({})
		, mXAfterImageDiff(8.0f)
		, mYAfterImageDiff(8.0f)
		, mbIsLeftKeyPressing(false)
		, mbIsRightKeyPressing(false)
		, mbIsUpKeyPressing(false)
		, mbIsDownKeyPressing(false)
	{
		mSpriteSheet.reserve(4);
		mFunc.BlendOp = AC_SRC_OVER;
		mFunc.BlendFlags = 0;
		mFunc.AlphaFormat = AC_SRC_ALPHA;
		mFunc.SourceConstantAlpha = 255;
	}
	void PlayerCustomAnimation::Tick()
	{
		if (mpAnimator != nullptr)
		{
			mIntervalCounter += Time::DeltaTime();
			if (mIntervalCounter >= mMinAnimInterval)
			{
				mIntervalCounter = 0.0f;
				++mCurrSpriteIdx;
				if (mCurrSpriteIdx >= mSpriteSheet.size())
					{ mCurrSpriteIdx = 0; }
			}

			if (IS_KEY_PRESSED(eKeyCode::A))
			{ mbIsLeftKeyPressing = true; }			
			if (IS_KEY_PRESSED(eKeyCode::D))
			{ mbIsRightKeyPressing = true; }			
/*			if (IS_KEY_PRESSED(eKeyCode::W))
			{ mbIsUpKeyPressing = true; }		*/	
			if (IS_KEY_PRESSED(eKeyCode::S))
			{ mbIsDownKeyPressing = true; }
		}

		
	}

	void PlayerCustomAnimation::Render(HDC hdc)
	{
		GameObject* pGameObject = mpAnimator->GetOwner();
		Vector2 pos = pGameObject->GetPos();
		pos = Camera::ToCameraPos(pos);
		pos += mSpriteSheet[mCurrSpriteIdx].Offset;

		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mSpriteSheet[mCurrSpriteIdx].Size.x / 2.0f),
			static_cast<int>(pos.y - mSpriteSheet[mCurrSpriteIdx].Size.y / 2.0f),
			static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x * mScale.x),
			static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y * mScale.y),

			mpImage->GetDC(),
			static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.x),
			static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.y),
			static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x),
			static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y),
			mFunc
		);

		mFunc.SourceConstantAlpha = 128;
		// AfterImage Effect Part
		if (mbIsLeftKeyPressing)
		{
			AlphaBlend(
				hdc,
				static_cast<int>((pos.x - mSpriteSheet[mCurrSpriteIdx].Size.x / 2.0f) + mXAfterImageDiff),
				static_cast<int>(pos.y - mSpriteSheet[mCurrSpriteIdx].Size.y / 2.0f),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x * mScale.x),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y * mScale.y),

				mpImage->GetDC(),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.x),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.y),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y),
				mFunc
			);
			mbIsLeftKeyPressing = false;
		}
		else if (mbIsRightKeyPressing)
		{
			AlphaBlend(
				hdc,
				static_cast<int>((pos.x - mSpriteSheet[mCurrSpriteIdx].Size.x / 2.0f) + -mXAfterImageDiff),
				static_cast<int>(pos.y - mSpriteSheet[mCurrSpriteIdx].Size.y / 2.0f),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x * mScale.x),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y * mScale.y),

				mpImage->GetDC(),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.x),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.y),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y),
				mFunc
			);
			mbIsRightKeyPressing = false;
		}
		//else if (mbIsUpKeyPressing)
		//{
		//	AlphaBlend(
		//		hdc,
		//		static_cast<int>(pos.x - mSpriteSheet[mCurrSpriteIdx].Size.x / 2.0f),
		//		static_cast<int>((pos.y - mSpriteSheet[mCurrSpriteIdx].Size.y / 2.0f) +mYAfterImageDiff),
		//		static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x * mScale.x),
		//		static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y * mScale.y),

		//		mpImage->GetDC(),
		//		static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.x),
		//		static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.y),
		//		static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x),
		//		static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y),
		//		mFunc
		//	);
		//	mbIsUpKeyPressing = false;
		//}
		else if (mbIsDownKeyPressing)
		{
			AlphaBlend(
				hdc,
				static_cast<int>(pos.x - mSpriteSheet[mCurrSpriteIdx].Size.x / 2.0f),
				static_cast<int>((pos.y - mSpriteSheet[mCurrSpriteIdx].Size.y / 2.0f) + -mYAfterImageDiff),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x * mScale.x),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y * mScale.y),

				mpImage->GetDC(),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.x),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].LeftTop.y),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.x),
				static_cast<int>(mSpriteSheet[mCurrSpriteIdx].Size.y),
				mFunc
			);
			mbIsDownKeyPressing = false;
		}
		mFunc.SourceConstantAlpha = 255;
	}
	void PlayerCustomAnimation::Create(Image* pImage, Vector2 size, Vector2 offset, UINT spriteCount)
	{
		assert(pImage != nullptr);
		mpImage = pImage;
		for (UINT i = 0; i < spriteCount; ++i)
		{
			PlayerSprite sprite;
			sprite.LeftTop.x = size.x * i;
			sprite.LeftTop.y = 0.0f;
			sprite.Size = size;
			sprite.Offset = offset;
			mSpriteSheet.push_back(sprite);
		}
	}
}