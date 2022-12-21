#pragma once
#include "yaBGImageObject.h"

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
	private:
		//Collider* mpTopCollider;
		//Collider* mpBotCollider;
		//Collider* mpTopDeskCollider;
		//Collider* mpBotDeskCollider;
		//Collider* mpPianoSideBookCollider;
		//Collider* mpPianoMidBookCollider;
		//Collider* mpPianoCollider;
	};
}

