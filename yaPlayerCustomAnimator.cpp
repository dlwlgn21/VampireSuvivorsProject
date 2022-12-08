#include "yaPlayerCustomAnimator.h"
#include "yaPlayerCustomAnimation.h"
#include "yaImage.h"
#include "yaInput.h"

namespace ya
{
	PlayerCustomAnimator::PlayerCustomAnimator()
		: Component(eComponentType::PLAYER_ANIMATOR)
		, mpCurrAnim(nullptr)
		, mCurrPlayerDirection(ePlayerAnimState::LEFT)
	{
		for (int i = 0; i < static_cast<UINT>(ePlayerAnimState::COUNT); ++i)
		{
			mpAnims[i] = nullptr;
		}
	}
	PlayerCustomAnimator::~PlayerCustomAnimator()
	{
		for (int i = 0; i < static_cast<UINT>(ePlayerAnimState::COUNT); ++i)
		{
			if (mpAnims[i] != nullptr)
				{ delete mpAnims[i]; }
		}
	}
	void PlayerCustomAnimator::Tick()
	{
		if (mpCurrAnim != nullptr)
		{
			switch (mCurrPlayerDirection)
			{
			case ePlayerAnimState::LEFT:
				if (IS_KEY_DOWN(eKeyCode::A) || IS_KEY_PRESSED(eKeyCode::A) || 
					IS_KEY_DOWN(eKeyCode::W) || IS_KEY_PRESSED(eKeyCode::W) ||
					IS_KEY_DOWN(eKeyCode::S) || IS_KEY_PRESSED(eKeyCode::S))
					{ mpCurrAnim->Tick();}
				break;
			case ePlayerAnimState::RIGHT:
				if (IS_KEY_DOWN(eKeyCode::D) || IS_KEY_PRESSED(eKeyCode::D)	||
					IS_KEY_DOWN(eKeyCode::W) || IS_KEY_PRESSED(eKeyCode::W) ||
					IS_KEY_DOWN(eKeyCode::S) || IS_KEY_PRESSED(eKeyCode::S))
					{ mpCurrAnim->Tick(); }
				break;
			default:
				break;
			}
		}
	}
	void PlayerCustomAnimator::Render(HDC hdc)
	{
		if (mpCurrAnim != nullptr)
			{ mpCurrAnim->Render(hdc); }
	}

	void PlayerCustomAnimator::CreateAnimation(Image* pImage, Vector2 size, Vector2 offset, UINT spriteCount, float minAnimInterval, ePlayerAnimState dir)
	{
		assert(pImage != nullptr);
		mpAnims[static_cast<UINT>(dir)] = new PlayerCustomAnimation(minAnimInterval);
		mpAnims[static_cast<UINT>(dir)]->Create(pImage,  size, offset, spriteCount);
		mpAnims[static_cast<UINT>(dir)]->SetAnimator(this);
		mpAnims[static_cast<UINT>(dir)]->SetScale(GetOwner()->GetScale());
	}
	void PlayerCustomAnimator::Play(ePlayerAnimState dir)
	{
		mpCurrAnim = mpAnims[static_cast<UINT>(dir)];
		mCurrPlayerDirection = dir;
	}
}