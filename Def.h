#pragma once
#include <cassert>
#include "Common.h"

#define IS_KEY_PRESSED(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::PRESSED
#define IS_KEY_DOWN(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::DOWN
#define IS_KEY_UP(KEY) ya::Input::GetKeyState(KEY) == ya::eKeyState::UP

enum class eSceneType
{
	LOGO_SCENE,
	TITLE_SCENE,
	PLAY_SCENE,
	ENDING_SCENE,
	TOOL_SCENE,
	COUNT
};

enum class ePenColor
{
	RED,
	BLUE,
	GREEN,
	COUNT
};

enum class eBrushColor
{
	TRANS_PARENT,
	BLACK,
	GRAY,	// 160, 0, 67
	WHITE,
	COUNT
};

enum class eComponentType
{
	RIGID_BODY,
	COLLIDER,
	ANIMATOR,
	ANIMATION,
	SOUND,
	COUNT
};

#define MAX_COLLIDER_LAYER (16)
enum class eColliderLayer
{
	DEFAULT,

	// GameObjects
	BACKGROUND,
	TILE,
	PLAYER,
	PLAYER_PROJECTTILE,
	MONSTER,
	MONSTER_PROJECTTILE,
	GROUND,

	// UI
	BACKPACK,

	UI = MAX_COLLIDER_LAYER - 1,
	COUNT = MAX_COLLIDER_LAYER,
};


union UnionColliderID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};

	UINT64 ID;
};
typedef UnionColliderID UnionTileID;
enum class eCameraEffect
{
	FADE_IN,
	FADE_OUT,
	COUNT
};

#define TILE_SIZE_X (32)
#define TILE_SIZE_Y (32)
#define TILE_COLUMN_COUNT (8)
#define TILE_ROW_COUNT (3)
#define TILE_SCALE (2)

