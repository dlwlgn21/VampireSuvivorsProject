#include "yaAnimation.h"
#include "yaImage.h"
#include "yaAnimator.h"
#include "yaCamera.h"
#include "yaGameObejct.h"
#include "yaTime.h"
namespace ya
{
	Animation::Animation()
		: Entity()
		, mpImage(nullptr)
		, mpAnimator(nullptr)
		, mSpriteIdx(0)
		, mTimer(0.0f)
		, mScale(Vector2::ONE)
		, mbIsStart(false)
		, mbIsEnd(false)
		, mbIsComplete(false)
		, mbIsAffectedCamera(false)
	{
		mFunc.BlendOp = AC_SRC_OVER;
		mFunc.BlendFlags = 0;
		mFunc.AlphaFormat = AC_SRC_ALPHA;
		mFunc.SourceConstantAlpha = 255;
		mSpriteSheet.reserve(8);
	}

	void Animation::Tick()
	{
		if (mbIsComplete) 
			{ return; }
		mTimer += Time::DeltaTime();
		// mIntervalCounter >= mMinAnimInterval
		if (mTimer >= mSpriteSheet[mSpriteIdx].Durtation)
		{
			mTimer = 0.0f;
			//++mSpriteIdx;
			if (mSpriteIdx + 1 >= mSpriteSheet.size())	
				{ 
					mSpriteIdx = 0;
					mbIsComplete = true; 
				}
			else										
				{ ++mSpriteIdx; }
		}

	}
	void Animation::Render(HDC hdc)
	{
		GameObject* pGameObject = mpAnimator->GetOwner();
		Vector2 pos = pGameObject->GetPos();
		if (mbIsAffectedCamera) { pos = Camera::ToCameraPos(pos); }
		pos += mSpriteSheet[mSpriteIdx].Offset;

		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mSpriteSheet[mSpriteIdx].Size.x / 2.0f),
			static_cast<int>(pos.y - mSpriteSheet[mSpriteIdx].Size.y / 2.0f),
			static_cast<int>(mSpriteSheet[mSpriteIdx].Size.x * mScale.x),
			static_cast<int>(mSpriteSheet[mSpriteIdx].Size.y * mScale.y),

			mpImage->GetDC(),
			static_cast<int>(mSpriteSheet[mSpriteIdx].LeftTop.x),
			static_cast<int>(mSpriteSheet[mSpriteIdx].LeftTop.y),
			static_cast<int>(mSpriteSheet[mSpriteIdx].Size.x),
			static_cast<int>(mSpriteSheet[mSpriteIdx].Size.y),
			mFunc
		);
	}

	void Animation::Create(Image* pImage, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteCount, float duration, bool bIsAffectedCamera)
	{
		mpImage = pImage;
		mbIsAffectedCamera = bIsAffectedCamera;
		for (UINT i = 0; i < spriteCount; ++i)
		{
			Sprite sprite;
			sprite.LeftTop.x = leftTop.x + (size.x * i);
			sprite.LeftTop.y = leftTop.y;
			sprite.Size = size;
			sprite.Offset = offset;
			sprite.Durtation = duration;
			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mSpriteIdx = 0;
		mTimer = 0.0f;
		mbIsComplete = false;
	}
	void Animation::ResetWithoutSpriteIdx()
	{
		//mTimer = 0.0f;
		mbIsComplete = false;
	}
}