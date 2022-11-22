#pragma once
#include "yaComponent.h"

namespace ya
{
	enum class ePlayerDirection
	{
		LEFT,
		RIGHT,
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
			UINT spriteCount, float minAnimInterval, ePlayerDirection dir);

		void Play(ePlayerDirection dir);
		__forceinline ePlayerDirection GetCurrDir() { return mCurrPlayerDirection; }
	private:
		PlayerCustomAnimation* mpAnims[static_cast<UINT>(ePlayerDirection::COUNT)];
		PlayerCustomAnimation* mpCurrAnim;
		ePlayerDirection mCurrPlayerDirection;
	};
}

