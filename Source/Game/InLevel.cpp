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
#include <vector>
#include <cstdlib>		// for std::rand()
#include <winuser.h>	// for GetKeyState()

#include "../Config/keymap.h"
#include "../Config/scaler.h"

#define PLAYER_ATTACK_CD	15
#define PLAYER_ATTACK_TIME	5

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
	const Vector2i regularBoxSize = Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE;
	
	player.LoadBitmapByString({
        "resources/giraffe.bmp"
	}, RGB(255, 255, 255));
	player.SetScale(1);
	player.SetHitBox(regularBoxSize * 0.7);

	playerAttack.LoadBitmapByString({
        "resources/slashLeft.bmp",
        "resources/slashDown.bmp",
        "resources/slashRight.bmp",
        "resources/slashUp.bmp"
	}, RGB(25, 28, 36));
	playerAttack.SetScale(1);
	playerAttack.SetHitBox(regularBoxSize * 1.0);
	playerAttack.SetShow(false);

	map.loadBMPs(datapath);
	map.bmps.SetScale(SCALE_SIZE);

	map.setLevel(1);
	player.position = map.getInfo().startPosition * TILE_SIZE * SCALE_SIZE;

	rockManager.loadBMP();

	testExit.LoadBitmapByString({ // next level entry
        datapath + "/173.bmp"
	}, RGB(255, 255, 255));
	testExit.SetScale(4);
	testExit.SetShow(false);
	testExit.SetHitBox(regularBoxSize * 1.0);

	Bittermap::CameraPosition = &player.position;
}

/* helper functions BEGIN */
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

unsigned int getFrameIndexOfBitmapBy(Vector2i attackDirection) {
	if(attackDirection==Vector2i(0,1)){
		return 1; // Down
	}
	if(attackDirection==Vector2i(0,-1)){
		return 3; // Up
	}
	if(attackDirection.x == -1){
		return 2; // Left
	}
	if(attackDirection.x == 1){
		return 0; // Right
	}
	throw "wtf";
}
/* helper functions END */

void InLevel::OnMove()							// 移動遊戲元素
{
	//TODO: can change timer into cool thing
	// unsigned int deltaTime = CSpecialEffect::GetEllipseTime();
	// CSpecialEffect::SetCurrentTime();
	
	// player moving speed
	const int speed=20;
	{ /* player move and collision BEGIN */
		const Vector2i moveVec = getMoveVecByKeys();
		if(moveVec!=Vector2i(0,0)) attackDirection=moveVec;

		const HitboxPool collisionPool = map.hp + rockManager.getHitbox();
		for (int i = 0; i < speed; i++) {
			player.MoveWithCollision(moveVec, collisionPool);
		}
	} /* player move and collision END */

	{ /* player attack timer BEGIN */
		if(playerAttackTimer > 0) {
			playerAttackTimer--;
			if (player) {}
			playerAttack.SetShow(playerAttackTimer > PLAYER_ATTACK_CD);
		}
		playerAttack.position = player.position + attackDirection * TILE_SIZE * SCALE_SIZE;
	} /* player attack counter END */

	// Damage value caused by the attack.
	const int damage = 1;
	{ /* attack rock BEGIN */
		// A static set can be used to keep track of marked rocks until the end of the round of attack
		static std::set<Rock*> markedRocks = {};

		if ( playerAttack.isShown() ) { /* is attacking */
			std::set<Rock*> brokenRockPtrs = {};

			const auto 🗡️ = playerAttack.GetHitbox();
			// Loop through all the rocks that collide with the attack area
			vector<Rock*> 🗿🗿🗿 = rockManager.getCollisionWith(🗡️);
			for (const auto& 🗿 : 🗿🗿🗿) {
				if (markedRocks.count(🗿) != 0) continue;
				markedRocks.insert(🗿);

				🗿->health -= damage;
				if ( 🗿->health <= 0 ) {
					brokenRockPtrs.insert(🗿);
					// TODO: pick up
					// Add the rock as an item to the floor and the player's bag
					// Increase the player's score based on the type of rock
					// If the rock is at the testExit position, show the testExit
					if ( 🗿->position == testExit.position ) {
						testExit.SetShow();
					}
				}
			}
			rockManager.remove(brokenRockPtrs);
		} else { /* is not attacking */
			markedRocks.clear();
		} 
	} /* attack rock END */
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
				rockManager.clear();
			} else {
				const Rect playerHitbox = player.GetHitBox();
				const auto pps = map.getPlaceablePositions();
				do { // FIXED: rock generate at player spawn point would break collision system
					rockManager.createRocksOn(pps);
				} while (rockManager.getHitbox().Collide(playerHitbox).size() != 0);
			}
			break;
		case 'P': // player attack
			if(playerAttackTimer > 0) break; // cd-ing

			playerAttack.SetFrameIndexOfBitmap(
				getFrameIndexOfBitmapBy(attackDirection)
			);
			playerAttackTimer = PLAYER_ATTACK_TIME + PLAYER_ATTACK_CD;
			break;
		case 'E': // randomly create exit
			testExit.SetShow();
			auto pps = map.getPlaceablePositions();
			testExit.position = pps[std::rand()%pps.size()] * TILE_SIZE * SCALE_SIZE;
			break;
	}
	#endif /* DEBUG_KEY */

	switch (nChar) {
		case KEY_DO_ACTION: // Check/Do Action
			const Rect playerHitbox = player.GetHitBox();
			const Rect exitHitbox = testExit.GetHitBox();
			if (testExit.isShown() && Rect::isOverlay(playerHitbox, exitHitbox)) {
				// switch to next level
				if (!map.nextLevel()) // if no next level
					break;

				auto mapInfo = map.getInfo();

				/* generate rocks */
				// FIXME: remove entry position from placeable positions
				const auto pps = map.getPlaceablePositions();
				rockManager.createRocksOn(pps);

				/* generate exit */
				player.position = mapInfo.startPosition * TILE_SIZE * SCALE_SIZE;
				if (mapInfo.hasPresetExit) {
					testExit.position = mapInfo.presetExitPosition * TILE_SIZE * SCALE_SIZE;
					testExit.SetShow();
				} else {
					const auto rocksPositions = rockManager.getPositions();
					testExit.position = rocksPositions[std::rand() % rocksPositions.size()];
					testExit.SetShow(false);
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

	rockManager.drawRocks();
	testExit.Draw();
	player.Draw();
	playerAttack.Draw();

	map.drawFront();
	/* top layer */
}
