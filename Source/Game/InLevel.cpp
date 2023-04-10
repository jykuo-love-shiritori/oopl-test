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
	player.position = Vector2i(10,4) * TILE_SIZE * SCALE_SIZE;

	map.loadFile("resources/MapData/1.ttt");
	map.loadBMPs(datapath);
	map.bmps.SetScale(SCALE_SIZE);

	testRock.load();

	testExit.LoadBitmapByString({ // next level entry
        datapath + "/173.bmp"
	}, RGB(255, 255, 255));
	testExit.SetScale(4);
	testExit.isShow = false;

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

	HitboxPool bighp = map.hp + testRock.hp;
	const auto playerBoxSize = Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE * 0.7;
	for (int i = 0; i < speed; i++) {
		player.Move(moveVec);
		while (true) {
			auto playerHitbox = Rect::FromTopLeft(player.position, playerBoxSize);
			auto collitions = bighp.Collide(playerHitbox);
			if (collitions.size() == 0) break;

			auto totalReaction = Vector2i(0, 0);
			for (auto const &wallBox : collitions) {
				auto currDist = playerHitbox.getCenter() - wallBox.getCenter();

				auto limitDist = wallBox.getRadius() + playerHitbox.getRadius();
				auto reactionVec = Vector2i(
					(currDist.x >= 0 ? limitDist.x : -limitDist.x) - currDist.x,
					(currDist.y >= 0 ? limitDist.y : -limitDist.y) - currDist.y
				);

				if (abs(reactionVec.x) == abs(reactionVec.y)) {
					// nop
				}
				else if (abs(reactionVec.x) < abs(reactionVec.y)) {
					reactionVec.y = 0;
				}
				else {
					reactionVec.x = 0;
				}
				totalReaction = totalReaction + reactionVec;
			}
			if (moveVec.y == 0) {
				totalReaction.y = 0;
			}
			else if (moveVec.x == 0) {
				totalReaction.x = 0;
			}
			else {
				if (abs(totalReaction.x) == abs(totalReaction.y)) {
					// nop
				}
				else if (abs(totalReaction.x) > abs(totalReaction.y)) {
					totalReaction.y = 0;
				}
				else {
					totalReaction.x = 0;
				}
			}
			player.Move(totalReaction);
		}
	}
	/* player move and collision END */
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/* debug key START */
	switch (nChar) {
		case 'J': // next map
		case 'K': // previous map
			if(nChar=='J'){
				if(++phase > 15) phase--;
			} else { // nChar=='K'
				if(--phase < 0) phase++;
			}

			map.loadFile("resources/MapData/" + std::to_string(phase+1) + ".ttt");
			player.position=map.startPosition[phase] * TILE_SIZE * SCALE_SIZE; // hard code 1-16(0-15)
			break;
		case 'O': // create rock
			if(isPress(VK_SHIFT)){
				testRock = Rock();
				testRock.load();
			} else {
				const auto playerBoxSize = Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE * 0.7;
				const Rect playerHitbox = Rect::FromTopLeft(player.position, playerBoxSize);
				do { // FIXED: rock generate at player spawn point would break collision system
					testRock.createRocks(map);
				} while (testRock.hp.Collide(playerHitbox).size() != 0);
			}
			break;
		case 'E': // create exit
			testExit.isShow = true;
			auto pps = map.getPlaceablePositions();
			testExit.position = pps[std::rand()%pps.size()] * TILE_SIZE * SCALE_SIZE;
			break;
	}
	/* debug key END */

	switch (nChar) {
		case KEY_DO_ACTION: // Check/Do Action
			const Rect playerHitbox = Rect::FromTopLeft(player.position, Vector2i(1,1) * TILE_SIZE * SCALE_SIZE * 0.7);
			const Rect exitHitbox = Rect::FromTopLeft(testExit.position, Vector2i(1,1) * TILE_SIZE * SCALE_SIZE * 1);
			if (Rect::isOverlay(playerHitbox, exitHitbox)) {
				// switch to next level
				if(++phase > 15) phase--;
				map.loadFile("resources/MapData/" + std::to_string(phase+1) + ".ttt");
				player.position=map.startPosition[phase] * TILE_SIZE * SCALE_SIZE; // hard code 1-16(0-15)

				// create exit
				testExit.isShow = true;
				auto pps = map.getPlaceablePositions();
				testExit.position = pps[std::rand()%pps.size()] * TILE_SIZE * SCALE_SIZE;
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
	map.drawBack();

	map.drawBuilding();

	testExit.Draw();
	testRock.drawRocks();
	player.Draw();

	map.drawFront();
}
