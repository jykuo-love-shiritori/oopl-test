#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "stages.h"

#include <shobjidl_core.h>
#include <string>
#include <cmath>
#include <cstdlib>
#include <winuser.h>

#include "../Config/keymap.h"
#include "../Config/scaler.h"

using namespace game_framework;
using namespace game_framework::stage;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

InLevel::InLevel(CGame *g) : CGameState(g)
{
}

InLevel::~InLevel()
{
}

void InLevel::OnBeginState()
{
}

void InLevel::OnInit()  								// 遊戲的初值及圖形設定
{
	player.LoadBitmapByString({
        "resources/giraffe.bmp"
	}, RGB(255, 255, 255));
	player.SetScale(1);
	player.SetHitBox(Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE * 0.7);

	map.loadBMPs(datapath);
	map.bmps.SetScale(SCALE_SIZE);

	map.setLevel(1);
	player.position = map.getInfo().startPosition * TILE_SIZE * SCALE_SIZE;

	rockMan.loadBMP();

	testExit.LoadBitmapByString({ // next level entry
        datapath + "/173.bmp"
	}, RGB(255, 255, 255));
	testExit.SetScale(4);
	testExit.isShow = false;
	testExit.SetHitBox(Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE * 1.0);

	Bittermap::CameraPosition = &player.position;
}

/* helper functions START */
bool isPress(int key) {
	return GetKeyState(key) & 0x8000;
}
Vector2i getMoveVecByKeys() {
	Vector2i moveVec = Vector2i(0,0);
	if(isPress(KEY_MOVE_LEFT)){
		moveVec.x = -1;
	}
	if(isPress(KEY_MOVE_RIGHT)){
		moveVec.x = 1;
	}
	if(isPress(KEY_MOVE_UP)){
		moveVec.y = -1;
	}
	if(isPress(KEY_MOVE_DOWN)){
		moveVec.y = 1;
	}
	return moveVec;
}
/* helper functions START */

void InLevel::OnMove()							// 移動遊戲元素
{
	/* player move and collision START*/
	const int speed=20;
	const Vector2i moveVec = getMoveVecByKeys();

	const HitboxPool collisionPool = map.hp + rockMan.getHitbox();
	for (int i = 0; i < speed; i++) {
		player.MoveWithCollision(moveVec, collisionPool);
	}
	/* player move and collision END */
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	#define DEBUG_KEY
	#ifdef DEBUG_KEY

	int mapIndex = (int)map.getLevel();
	switch (nChar) {
		case 'J': // next map
		case 'K': // previous map
			if(nChar=='J'){
				if(mapIndex < 16) mapIndex++;
			} else { // nChar=='K'
				if(mapIndex != 1) mapIndex--;
			}
			map.setLevel(mapIndex);
			player.position = map.getInfo().startPosition * TILE_SIZE * SCALE_SIZE;
			break;
		case 'O': // randomly create/clear rock
			if(isPress(VK_SHIFT)){
				rockMan.clear();
			} else {
				const Rect playerHitbox = player.GetHitBox();
				const auto pps = map.getPlaceablePositions();
				do { // FIXED: rock generate at player spawn point would break collision system
					rockMan.createRocksOn(pps);
				} while (rockMan.getHitbox().Collide(playerHitbox).size() != 0);
			}
			break;
		case 'E': // randomly create exit
			testExit.isShow = true;
			auto pps = map.getPlaceablePositions();
			testExit.position = pps[std::rand()%pps.size()] * TILE_SIZE * SCALE_SIZE;
			break;
	}
	#endif /* DEBUG_KEY */

	switch (nChar) {
		case KEY_DO_ACTION: // Check/Do Action
			const Rect playerHitbox = player.GetHitBox();
			const Rect exitHitbox = testExit.GetHitBox();
			if (Rect::isOverlay(playerHitbox, exitHitbox)) {
				// switch to next level
				if (map.nextLevel()) // if no next level
					break;

				auto mapInfo = map.getInfo();
				player.position = mapInfo.startPosition * TILE_SIZE * SCALE_SIZE;
				if (mapInfo.hasPresetExit) {
					testExit.position = mapInfo.presetExitPosition * TILE_SIZE * SCALE_SIZE;
					testExit.isShow = true;
				} else {
					testExit.isShow = false;
					// FIXME: randomly create exit for test
					testExit.isShow = true;
					auto pps = map.getPlaceablePositions();
					testExit.position = pps[std::rand()%pps.size()] * TILE_SIZE * SCALE_SIZE;
				}
			}
			break;
	}
}

void InLevel::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void InLevel::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void InLevel::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void InLevel::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void InLevel::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void InLevel::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void InLevel::OnShow()
{
	/* bottom layer */
	map.drawBack();
	map.drawBuilding();

	rockMan.drawRocks();
	testExit.Draw();
	player.Draw();

	map.drawFront();
	/* top layer */
}
