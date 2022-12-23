#define MAP_TOP_BOT_COLLIDER_WIDTH (4096.0f)
#define MAP_TOP_BOT_COLLIDER_HEIGHT (5.0f)

#define MAP_TOP_BOT_COLLIDER_X_POS (0.0f)
#define MAP_BOT_COLLIDER_Y_POS (455.0f)
#define MAP_TOP_COLLIDER_Y_POS (-460.0f)

#define TOP_DESK_WIDTH (165.0f)
#define TOP_DESK_HEIGHT (50.0f)
#define TOP_DESK_X_POS (-412.0f)
#define TOP_DESK_Y_POS (-390.0f)

#define BOT_DESK_WIDTH (100.0f)
#define BOT_DESK_HEIGHT (50.0f)
#define BOT_DESK_X_POS (1340.0f)
#define BOT_DESK_Y_POS (310.0f)

#define PIANO_SIDE_BOOK_WIDTH (380.f)
#define PIANO_SIDE_BOOK_HEIGHT (120.f)
#define PIANO_SIDE_BOOK_X_POS (-1410.0f)
#define PIANO_SIDE_BOOK_Y_POS (-130.f)

#define PIANO_MID_BOOK_WIDTH (190.0f)
#define PIANO_MID_BOOK_HEIGHT (50.0f)
#define PIANO_MID_BOOK_X_POS (-1440.0f)
#define PIANO_MID_BOOK_Y_POS (-220.f)

#define PIANO_WIDTH (126.0f)
#define PIANO_HEIGHT (30.0f)
#define PIANO_X_POS (-1437.0f)
#define PIANO_Y_POS (-50.f)

#define SCROLL_CHECKER_WIDTH (40.0f)

#include "yaBGGmaeImage.h"
#include "yaImage.h"
#include "yaCamera.h"
#include "yaObject.h"
#include "yaCollider.h"
#include "yaGameMapCollider.h"

namespace ya
{


	unsigned char BGGmaeImage::mLeftScrollCount = 0;
	unsigned char BGGmaeImage::mRightScrollCount = 0;

	BGGmaeImage::BGGmaeImage(const std::wstring& key, const std::wstring& path)
		: BGImageObject(key, path)
		, mbIsLeftScrollCheck(false)
		, mbIsRightScrollCheck(false)
	{
		mPos = Vector2::ZERO;
	}
	void BGGmaeImage::Initialize()
	{
		if (mbIsLeftScrollCheck == false && mbIsRightScrollCheck == false)
		{
			instantiate(eMapColliderType::TOP,					Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT),	Vector2(MAP_TOP_BOT_COLLIDER_X_POS, MAP_TOP_COLLIDER_Y_POS));
			instantiate(eMapColliderType::BOT,					Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT),	Vector2(MAP_TOP_BOT_COLLIDER_X_POS, MAP_BOT_COLLIDER_Y_POS));
			instantiate(eMapColliderType::TOP_DESK,				Vector2(TOP_DESK_WIDTH, TOP_DESK_HEIGHT),							Vector2(TOP_DESK_X_POS, TOP_DESK_Y_POS));
			instantiate(eMapColliderType::BOT_DESK,				Vector2(BOT_DESK_WIDTH, BOT_DESK_HEIGHT),							Vector2(BOT_DESK_X_POS, BOT_DESK_Y_POS));
			instantiate(eMapColliderType::PIANO_SIDE_BOOK,		Vector2(PIANO_SIDE_BOOK_WIDTH, PIANO_SIDE_BOOK_HEIGHT),				Vector2(PIANO_SIDE_BOOK_X_POS, PIANO_SIDE_BOOK_Y_POS));
			instantiate(eMapColliderType::PIANO_MID_BOOK,		Vector2(PIANO_MID_BOOK_WIDTH, PIANO_MID_BOOK_HEIGHT),				Vector2(PIANO_MID_BOOK_X_POS, PIANO_MID_BOOK_Y_POS));
			instantiate(eMapColliderType::PIANO,				Vector2(PIANO_WIDTH, PIANO_HEIGHT),									Vector2(PIANO_X_POS, PIANO_Y_POS));
			instantiate(eMapColliderType::LEFT_SCROLL_CHECKER,	Vector2(SCROLL_CHECKER_WIDTH, SCREEN_HEIGHT),						Vector2(-MAP_TOP_BOT_COLLIDER_WIDTH / 4, 0.0f));
			instantiate(eMapColliderType::RIGHT_SCROLL_CHECKER, Vector2(SCROLL_CHECKER_WIDTH, SCREEN_HEIGHT),						Vector2(MAP_TOP_BOT_COLLIDER_WIDTH / 4, 0.0f));
			return;
		}
		unsigned char leftScrollCount = BGGmaeImage::GetLeftScrollCount();
		unsigned char rightScrollCount = BGGmaeImage::GetRightScrollCount();

		if (mbIsLeftScrollCheck)
		{
			mPos.x = -leftScrollCount * MAP_TOP_BOT_COLLIDER_WIDTH;
			instantiate(eMapColliderType::TOP,					Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT),	Vector2((MAP_TOP_BOT_COLLIDER_X_POS - (MAP_TOP_BOT_COLLIDER_WIDTH * leftScrollCount)), MAP_TOP_COLLIDER_Y_POS));
			instantiate(eMapColliderType::BOT,					Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT),	Vector2((MAP_TOP_BOT_COLLIDER_X_POS - (MAP_TOP_BOT_COLLIDER_WIDTH * leftScrollCount)), MAP_BOT_COLLIDER_Y_POS));
			instantiate(eMapColliderType::TOP_DESK,				Vector2(TOP_DESK_WIDTH, TOP_DESK_HEIGHT),							Vector2((TOP_DESK_X_POS - (MAP_TOP_BOT_COLLIDER_WIDTH * leftScrollCount)), TOP_DESK_Y_POS));
			instantiate(eMapColliderType::BOT_DESK,				Vector2(BOT_DESK_WIDTH, BOT_DESK_HEIGHT),							Vector2((BOT_DESK_X_POS - (MAP_TOP_BOT_COLLIDER_WIDTH * leftScrollCount)) , BOT_DESK_Y_POS));
			instantiate(eMapColliderType::PIANO_SIDE_BOOK,		Vector2(PIANO_SIDE_BOOK_WIDTH, PIANO_SIDE_BOOK_HEIGHT),				Vector2((PIANO_SIDE_BOOK_X_POS - (MAP_TOP_BOT_COLLIDER_WIDTH * leftScrollCount)) , PIANO_SIDE_BOOK_Y_POS));
			instantiate(eMapColliderType::PIANO_MID_BOOK,		Vector2(PIANO_MID_BOOK_WIDTH, PIANO_MID_BOOK_HEIGHT),				Vector2((PIANO_MID_BOOK_X_POS - (MAP_TOP_BOT_COLLIDER_WIDTH * leftScrollCount)), PIANO_MID_BOOK_Y_POS));
			instantiate(eMapColliderType::PIANO,				Vector2(PIANO_WIDTH, PIANO_HEIGHT),									Vector2((PIANO_X_POS - (MAP_TOP_BOT_COLLIDER_WIDTH * leftScrollCount)), PIANO_Y_POS));
			instantiate(eMapColliderType::LEFT_SCROLL_CHECKER,	Vector2(SCROLL_CHECKER_WIDTH, SCREEN_HEIGHT),						Vector2(((-MAP_TOP_BOT_COLLIDER_WIDTH / 4) - (MAP_TOP_BOT_COLLIDER_WIDTH * leftScrollCount)), 0.0f));
		}
		else
		{
			mPos.x = rightScrollCount * MAP_TOP_BOT_COLLIDER_WIDTH;
			instantiate(eMapColliderType::TOP,					Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT),	Vector2((MAP_TOP_BOT_COLLIDER_X_POS + (MAP_TOP_BOT_COLLIDER_WIDTH * rightScrollCount)), MAP_TOP_COLLIDER_Y_POS));
			instantiate(eMapColliderType::BOT,					Vector2(MAP_TOP_BOT_COLLIDER_WIDTH, MAP_TOP_BOT_COLLIDER_HEIGHT),	Vector2((MAP_TOP_BOT_COLLIDER_X_POS + (MAP_TOP_BOT_COLLIDER_WIDTH * rightScrollCount)), MAP_BOT_COLLIDER_Y_POS));
			instantiate(eMapColliderType::TOP_DESK,				Vector2(TOP_DESK_WIDTH, TOP_DESK_HEIGHT),							Vector2((TOP_DESK_X_POS + (MAP_TOP_BOT_COLLIDER_WIDTH * rightScrollCount)), TOP_DESK_Y_POS));
			instantiate(eMapColliderType::BOT_DESK,				Vector2(BOT_DESK_WIDTH, BOT_DESK_HEIGHT),							Vector2((BOT_DESK_X_POS + (MAP_TOP_BOT_COLLIDER_WIDTH * rightScrollCount)), BOT_DESK_Y_POS));
			instantiate(eMapColliderType::PIANO_SIDE_BOOK,		Vector2(PIANO_SIDE_BOOK_WIDTH, PIANO_SIDE_BOOK_HEIGHT),				Vector2((PIANO_SIDE_BOOK_X_POS + (MAP_TOP_BOT_COLLIDER_WIDTH * rightScrollCount)), PIANO_SIDE_BOOK_Y_POS));
			instantiate(eMapColliderType::PIANO_MID_BOOK,		Vector2(PIANO_MID_BOOK_WIDTH, PIANO_MID_BOOK_HEIGHT),				Vector2((PIANO_MID_BOOK_X_POS + (MAP_TOP_BOT_COLLIDER_WIDTH * rightScrollCount)), PIANO_MID_BOOK_Y_POS));
			instantiate(eMapColliderType::PIANO,				Vector2(PIANO_WIDTH, PIANO_HEIGHT),									Vector2((PIANO_X_POS + (MAP_TOP_BOT_COLLIDER_WIDTH * rightScrollCount)), PIANO_Y_POS));
			instantiate(eMapColliderType::RIGHT_SCROLL_CHECKER, Vector2(SCROLL_CHECKER_WIDTH, SCREEN_HEIGHT),						Vector2(((MAP_TOP_BOT_COLLIDER_WIDTH / 4) + (MAP_TOP_BOT_COLLIDER_WIDTH * rightScrollCount)), 0.0f));
		}
	}
	void BGGmaeImage::Tick()
	{
		GameObject::Tick();
	}
	void BGGmaeImage::Render(HDC hdc)
	{
		Vector2 pos = Camera::ToCameraPos(mPos);

		AlphaBlend(
			hdc,
			static_cast<int>(pos.x - mImgWidth / 2.0f),
			static_cast<int>(pos.y - mImgHeigt / 2.0f),
			static_cast<int>(mImgWidth),
			static_cast<int>(mImgHeigt),

			mpImage->GetDC(),
			0,
			0,
			mImgWidth,
			mImgHeigt,
			mBlendFunc
		);
		GameObject::Render(hdc);
	}
	unsigned char BGGmaeImage::GetLeftScrollCount()
	{
		return mLeftScrollCount;
	}
	unsigned char BGGmaeImage::GetRightScrollCount()
	{
		return mRightScrollCount;
	}
	void BGGmaeImage::IncreaseLeftScrollCount()
	{
		++mLeftScrollCount;
	}
	void BGGmaeImage::IncreaseRightScrollCount()
	{
		++mRightScrollCount;
	}
	void BGGmaeImage::instantiate(eMapColliderType type, Vector2 colliderSize, Vector2 colliderOffset)
	{
		GameMapCollider* pGameObject = new GameMapCollider(type, colliderSize, colliderOffset);
		//const UINT NAME_BUFFER_COUNT = 32;
		//wchar_t name[NAME_BUFFER_COUNT];
		//switch (type)
		//{
		//case ya::eMapColliderType::TOP:
		//	swprintf_s(name, NAME_BUFFER_COUNT, L"TOP");
		//	break;
		//case ya::eMapColliderType::BOT:
		//	swprintf_s(name, NAME_BUFFER_COUNT, L"BOT");
		//	break;
		//case ya::eMapColliderType::TOP_DESK:
		//	swprintf_s(name, NAME_BUFFER_COUNT, L"TOP_DESK");
		//	break;
		//case ya::eMapColliderType::BOT_DESK:
		//	swprintf_s(name, NAME_BUFFER_COUNT, L"BOT_DESK");
		//	break;
		//case ya::eMapColliderType::PIANO_SIDE_BOOK:
		//	swprintf_s(name, NAME_BUFFER_COUNT, L"PIANO_SIDE_BOOK");
		//	break;
		//case ya::eMapColliderType::PIANO_MID_BOOK:
		//	swprintf_s(name, NAME_BUFFER_COUNT, L"PIANO_MID_BOOK");
		//	break;
		//case ya::eMapColliderType::PIANO:
		//	swprintf_s(name, NAME_BUFFER_COUNT, L"PIANO");
		//	break;
		//case ya::eMapColliderType::LEFT_SCROLL_CHECKER:
		//	swprintf_s(name, NAME_BUFFER_COUNT, L"LEFT_SCROLL_CHECKER");
		//	break;
		//case ya::eMapColliderType::RIGHT_SCROLL_CHECKER:
		//	swprintf_s(name, NAME_BUFFER_COUNT, L"RIGHT_SCROLL_CHECKER");
		//	break;
		//default:
		//	break;
		//}
		//wchar_t buffer[128];
		//swprintf_s(buffer, 128, L"%s Pos{%1.f, %1.f}\n", name, pGameObject->GetPos().x, pGameObject->GetPos().y);
		//OutputDebugStringW(buffer);
		Scene* scene = SceneManager::GetSpecifiedScene(eSceneType::PLAY_SCENE);
		scene->AddGameObject(static_cast<GameObject*>(pGameObject), eColliderLayer::BACKGROUND);
	}
}