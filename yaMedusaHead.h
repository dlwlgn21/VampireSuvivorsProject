#pragma once
#include "yaMonster.h"

namespace ya
{
	class Image;
	class Animator;
	class Collider;
	class Player;
	class ExpGemObjPool;
	class MedusaHead final : public Monster
	{
	public:
		MedusaHead(
			const MonsterCreateInfo& monInfo,
			const std::wstring& imageRightMoveKey,
			const std::wstring& imageLeftMoveKey,
			const std::wstring& imageRightDeathKey,
			const std::wstring& imageLeftDeathKey,
			const std::wstring& imageRightHittedKey,
			const std::wstring& imageLeftHittedKey,


			const std::wstring& imageRightMovePath,
			const std::wstring& imageLeftMovePath,
			const std::wstring& imageRightDeathPath,
			const std::wstring& imageLeftDeathPath,
			const std::wstring& imageRightHittedPath,
			const std::wstring& imageLeftHittedPath,
			ExpGemObjPool* pExpGemObjPool,
			MonsterObjPool<Monster>* pMonsterObjPool
		);
		virtual ~MedusaHead() = default;

		void Tick() override;
		void Render(HDC hdc) override;
	private:
		float mAccumVal;
	};
}

