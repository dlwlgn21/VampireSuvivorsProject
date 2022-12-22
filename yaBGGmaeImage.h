#pragma once
#include "yaBGImageObject.h"
#include "yaGameMapCollider.h"

namespace ya
{
	//class Collider;
	class BGGmaeImage final : public BGImageObject 
	{
	public:
		BGGmaeImage(const std::wstring& key, const std::wstring& path);
		BGGmaeImage(const BGGmaeImage& other) = delete;
		BGGmaeImage& operator=(const BGGmaeImage& other) = delete;
		virtual ~BGGmaeImage() = default;

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;
		__forceinline void SetLeftScrollCheck(bool isLeftScrollCheck) { mbIsLeftScrollCheck = isLeftScrollCheck; }
		__forceinline void SetRightScrollCheck(bool isRightScrollCheck) { mbIsLeftScrollCheck = isRightScrollCheck; }
		
		static unsigned char GetRightScrollCount();
		static unsigned char GetLeftScrollCount();
		static void IncreaseLeftScrollCount();
		static void IncreaseRightScrollCount();

	private:
		void instantiate(eMapColliderType type, Vector2 colliderSize, Vector2 colliderOffset);

	private:
		bool mbIsLeftScrollCheck;
		bool mbIsRightScrollCheck;
		static unsigned char mLeftScrollCount;
		static unsigned char mRightScrollCount;
	};
}

