#pragma once
#include "yaComponent.h"

namespace ya
{
	enum class ePlayerAnimState
	{
		LEFT,
		LEFT_HITTED,
		RIGHT,
		RIGHT_HITTED,
		COUNT
	};
	class Image;
	class PlayerCustomAnimation;
	class PlayerCustomAnimator final : public Component
	{
	public:
		PlayerCustomAnimator();
		virtual ~PlayerCustomAnimator();

		void Tick() override;
		void Render(HDC hdc) override;

		void CreateAnimation(
			Image* pImage, Vector2 leftTop,
			Vector2 size, Vector2 offset,
			UINT spriteCount, float minAnimInterval, ePlayerAnimState dir);

		void Play(ePlayerAnimState dir);
		__forceinline ePlayerAnimState GetCurrDir() { return mCurrPlayerDirection; }
	private:
		PlayerCustomAnimation* mpAnims[static_cast<UINT>(ePlayerAnimState::COUNT)];
		PlayerCustomAnimation* mpCurrAnim;
		ePlayerAnimState mCurrPlayerDirection;
	};
}

