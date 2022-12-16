#include "yaLevelUpArrow.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaSceneManager.h"
#include "yaUIManager.h"
#include "yaInput.h"

namespace ya
{
	LevelUpArrow::LevelUpArrow()
		: UIAnimObject(eUIType::PLAY_LEVEL_UP)
		, mImgWidth(0)
		, mImgHeight(0)
		, M_MOVE_AMOUNT(174.0f)
		, M_MAX_UP_POS(300)
		, M_MIN_DOWN_POS(700)
	{
		mpAnimImage = Resources::Load<Image>(L"ArrowAnim", L"Resources\\Image\\LevelSelectionArrowAnim.bmp");
		assert(mpAnimImage != nullptr);
		mAnimSize = Vector2(711, 41.0f);
		Create(mpAnimImage, mAnimSize, Vector2(-280.0f, -100.0f), 8, ARROW_ANIM_DURATION, false);
		mImgWidth = static_cast<int>(mAnimSize.x);
		mImgHeight = static_cast<int>(mAnimSize.y);
		mSize = Vector2(mAnimSize.x, mAnimSize.y);
		mPos = Vector2(SCREEN_WIDTH / 2.0f - mAnimSize.x / 2, 347.0f);
		mbIsSelected = false;
	}
	void LevelUpArrow::OnInitialize()
	{
	}
	void LevelUpArrow::OnActive()
	{
	}
	void LevelUpArrow::OnInactive()
	{
	}
	void LevelUpArrow::OnTick()
	{
		UIAnimObject::OnTick();
		if (IS_KEY_DOWN(eKeyCode::W) || IS_KEY_DOWN(eKeyCode::UP))
		{
			if (static_cast<int>(mPos.y - M_MOVE_AMOUNT) <= M_MAX_UP_POS)
			{
				return;
			}
			mPos.y -= M_MOVE_AMOUNT;
		}
		else if (IS_KEY_DOWN(eKeyCode::S) || IS_KEY_DOWN(eKeyCode::DOWN))
		{
			if (static_cast<int>(mPos.y + M_MOVE_AMOUNT) >= M_MIN_DOWN_POS)
			{
				return;
			}
			mPos.y += M_MOVE_AMOUNT;
		}
	}
	void LevelUpArrow::OnRender(HDC hdc)
	{
		Sprite& sprite = mSpriteSheet[mCurrSpriteIdx];
		Vector2 offset = sprite.Offset;
		AlphaBlend(
			hdc,
			static_cast<int>(mScreenPos.x + offset.x - sprite.Size.x / 2),
			static_cast<int>(mScreenPos.y + offset.y - sprite.Size.y / 2),
			static_cast<int>(sprite.Size.x),
			static_cast<int>(sprite.Size.y),

			mpAnimImage->GetDC(),
			static_cast<int>(sprite.LeftTop.x),
			static_cast<int>(sprite.LeftTop.y),
			static_cast<int>(sprite.Size.x),
			static_cast<int>(sprite.Size.y),
			mBlendFunc
		);
	}
	void LevelUpArrow::OnUIClear()
	{
	}
	void LevelUpArrow::ButtonClicked()
	{
	}
}