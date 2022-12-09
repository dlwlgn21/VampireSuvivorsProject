#pragma once
#include "yaSelectionMenuIcon.h"

namespace ya
{
	class StageLibraryIcon final : public SelectionMenuIcon
	{
	public:
		StageLibraryIcon();
		StageLibraryIcon(const StageLibraryIcon& other) = delete;
		StageLibraryIcon& operator=(const StageLibraryIcon& other) = delete;
		virtual ~StageLibraryIcon() = default;

		void OnInitialize() override;
		void OnActive() override;
		void OnInactive() override;
		void OnTick() override;
		void OnRender(HDC hdc) override;
		void OnUIClear() override;
	private:
		int mNoSelelctedImgWidth;
		int mNoSelelctedImgHeight;
		int mSelelctedImgWidth;
		int mSelelctedImgHeight;
		Vector2 mOffset;
	};

}

