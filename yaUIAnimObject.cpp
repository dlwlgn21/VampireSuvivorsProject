#include "yaUIAnimObject.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaTime.h"

namespace ya
{
	/*
		Image* mpAnimImage;
		std::vector<Sprite> mSpriteSheet;
		BLENDFUNCTION mFunc;
		UINT mSpriteIdx;
		Vector2 mScale;
		float mTimer;
		bool mbIsAffectedCamera;
	*/
	UIAnimObject::UIAnimObject(eUIType type)
		: UIBase(type)
		, mpAnimImage(nullptr)
		, mpCurrRenderImage(nullptr)
		, mBlendFunc({})
		, mCurrSpriteIdx(0)
		, mScale(Vector2::ONE)
		, mAnimSize(Vector2::ZERO)
		, mTimer(0.0f)
		, mbIsAffectedCamera(false)
		, mAnimDuration(0.0f)
		, mbIsSelected(false)
	{
		mBlendFunc.BlendOp = AC_SRC_OVER;
		mBlendFunc.BlendFlags = 0;
		mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
		mBlendFunc.SourceConstantAlpha = 255;
		mSpriteSheet.reserve(8);
		mpNonAnimImage = mpImage;
		//assert(mpNonAnimImage != nullptr);
	}

	void UIAnimObject::Create(Image* pImage, Vector2 size, Vector2 offset, UINT spriteCount, float duration, bool bIsAffectedCamera)
	{
		assert(pImage != nullptr);
		mbIsAffectedCamera = bIsAffectedCamera;
		mAnimDuration = duration;
		Sprite sprite;
		for (UINT i = 0; i < spriteCount; ++i)
		{
			sprite.LeftTop.x = size.x * i;
			sprite.LeftTop.y = 0.0f;
			sprite.Size = size;
			sprite.Offset = offset;
			mSpriteSheet.push_back(sprite);
		}
	}

	void UIAnimObject::ResetWithoutSpriteIdx()
	{
	}
	void UIAnimObject::OnInitialize()
	{
	}
	void UIAnimObject::OnActive()
	{
	}
	void UIAnimObject::OnInactive()
	{
	}
	void UIAnimObject::OnTick()
	{
		mTimer += Time::DeltaTime();
		if (mTimer >= mAnimDuration)
		{
			mTimer = 0.0f;
			++mCurrSpriteIdx;
			if (mCurrSpriteIdx >= mSpriteSheet.size())
				{ mCurrSpriteIdx = 0; }
		}
	}
	void UIAnimObject::OnRender(HDC hdc)
	{
	}
	void UIAnimObject::OnUIClear()
	{
	}
}