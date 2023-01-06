#pragma once
#include <cassert>
#include "Common.h"

#define IS_KEY_PRESSED(KEY) (ya::Input::GetKeyState(KEY) == ya::eKeyState::PRESSED)
#define IS_KEY_DOWN(KEY) (ya::Input::GetKeyState(KEY) == ya::eKeyState::DOWN)
#define IS_KEY_UP(KEY) (ya::Input::GetKeyState(KEY) == ya::eKeyState::UP)

enum class eSceneType
{
	TITLE_SCENE,
	PLAY_SCENE,
	RESULT_SCENE,
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
	PLAYER_ANIMATOR,
	ANIMATOR,
	PLAYER_ANIMATION,
	ANIMATION,
	SOUND,
	COUNT
};

constexpr UINT MAX_COLLIDER_LAYER = 16;
enum class eColliderLayer
{
	DEFAULT,

	// GameObjects
	BACKGROUND,
	EXP_JEM,
	PLAYER_PROJECTTILE,
	MONSTER,
	PLAYER,

	// UI

	UI = MAX_COLLIDER_LAYER - 1,
	COUNT = MAX_COLLIDER_LAYER,
};

enum class eUIType
{
	START_MENU_SELECTION,
	CHARACTER_SELECTION,
	STAGE_SELECTION,
	PLAY_INFO_HUD,
	PLAY_LEVEL_UP,
	PLAY_PAUSED,
	GAME_OVER,
	COUNT
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

enum class eWeaponAndItemTypes
{
	KNIFE,
	FIRE_WAND,
	RUNE,
	AXE,
	WEAPON_SPEED,
	WEAPON_DAMAGE,
	MOVE_SPEED,
	PLAYER_AMOUR,
	COUNT
};


enum class eMonsterState
{
	PATROL,
	TRACE,
	DEAD,
	COUNT
};
enum class eMonsterType
{
	MUDMAN,
	GREEN_GHOST,
	MEDUSA_HEAD,
	BOSS_MIRA,
	COUNT
};

const constexpr float  DIAGONAL_CORRECTION_VALUE = 0.75f;
const constexpr UINT  MAX_KNIFE_COUNT = 15;
const constexpr UINT  MAX_RUNE_TRACER_COUNT = 5;
const constexpr float  BG_BLACK_BAR_Y_DIFF = 10.0f;
const constexpr float  GAME_SCREEN_X_DIFF = 160.0f;
 
const constexpr float BLACK_BAR_X_DIFF = 95.0f;
const constexpr float BLACK_BAR_HEIGHT = 101.0f;
const constexpr float CHARACTOR_ICON_X_DIFF = 20.0f;
const constexpr float CHARACTOR_IOCN_Y_DIFF = 80.0f;
const constexpr float ARROW_ANIM_DURATION = 0.25f;
 
const constexpr UINT SCREEN_WIDTH = 1920;
const constexpr UINT SCREEN_HEIGHT = 1080;
const constexpr UINT ACTUAL_GAME_SCREEN_WIDTH = 1727;
const constexpr UINT ACTUAL_GAME_SCREEN_X_DIFF = 96;
const constexpr UINT CAMERA_MASK_WIDTH = 95;
const constexpr UINT EXP_BAR_HEIGHT = 43;
 
const constexpr UINT ONE_MIN_NORMAL_MONSTER_EXP = 100;
const constexpr UINT MUDMAN_INITIAL_HP = 5;
const constexpr UINT MUDMAN_INITIAL_DAMAGE = 5;
const constexpr float MUDMAN_INITIAL_SPEED = 120.0f;
 
const constexpr UINT GREEN_GHOST_INITIAL_HP = 10;
const constexpr UINT GREEN_GHOST_INITIAL_DAMAGE = 3;
const constexpr float GREEN_GHOST_INITIAL_SPEED = 80.0f;
 
const constexpr UINT MEDUSA_HEAD_INITIAL_HP = 10;
const constexpr UINT MEDUSA_HEAD_INITIAL_DAMAGE = 2;
const constexpr float MEDUSA_HEAD_INITIAL_SPEED = 200.0f;
const constexpr UINT TOTAL_WEAPON_COUNT = 4;
const constexpr UINT TOTAL_STAT_BURF_ITEM_COUNT = 4;

const constexpr UINT MAX_WEAPON_STAT_BURF_ITEM_COUNT = (TOTAL_WEAPON_COUNT + TOTAL_STAT_BURF_ITEM_COUNT);
const constexpr UINT MAX_WEAPON_LEVEL = 5;
const constexpr UINT MAX_STAT_BURF_ITEM_LEVEL = 4;
const constexpr float LEVEL_IMG_HEIGHT = 174.0f;
const constexpr UINT EXP_BLUE_GEM = 30;
