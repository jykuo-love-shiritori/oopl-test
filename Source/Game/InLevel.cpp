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

	userInterface.load();

	rockManager.loadBMP();

	testExit.LoadBitmapByString({ // next level entry
        datapath + "/173.bmp"
	}, RGB(255, 255, 255));
	testExit.SetScale(4);
	testExit.SetShow(false);
	testExit.SetHitBox(regularBoxSize * 1.0);

	bug.load();
	bombAnime.init();

	Bittermap::CameraPosition = &player.position;
	userInterface.setHealth(&playerHP);
}

void InLevel::OnBeginState()
{
	map.setLevel(1);

	userInterface.setScore(0);

	auto mapInfo = map.getInfo();
	SetupLevel(mapInfo);

	bug.init(Vector2i(100,100));
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

void InLevel::SetupLevel(Map::Info mapInfo) {
	/* generate rocks */
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
/* helper functions END */

void InLevel::OnMove()							// 移動遊戲元素
{
	//TODO: can change timer into cool thing
	// unsigned int deltaTime = CSpecialEffect::GetEllipseTime();
	// CSpecialEffect::SetCurrentTime();
	
	// #define NO_COLLISION

	// player moving speed
	const int speed=20;
	{ /* player move and collision BEGIN */
		const Vector2i moveVec = getMoveVecByKeys();
		if(moveVec!=Vector2i(0,0)) attackDirection=moveVec;

		const HitboxPool collisionPool = map.hp + rockManager.getHitbox();
		for (int i = 0; i < speed; i++) {
			#ifndef NO_COLLISION
			player.MoveWithCollision(moveVec, collisionPool);
			#else /* NO_COLLISION */
			player.Move(moveVec);
			#endif /* NO_COLLISION */
		}
	} /* player move and collision END */

	/*bug pursuit BEGIN */
	bug.pursuit(player.position);
	/*bug pursuit END */
	{/*bug collision BEGIN */
		const auto p = bug.getPosition();
		if (
			Rect::isOverlay(player.GetHitbox(), Rect::FromTopLeft(p, {50,50}))
		) {
			playerHP--;
		}
	}/*bug collision END */

	{ /* player attack timer BEGIN */
		if(playerAttackTimer > 0) {
			playerAttackTimer--;
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

			const auto 🗡️ = playerAttack.GetHitbox();
			// Loop through all the rocks that collide with the attack area
			const vector<Rock*> 🗿🗿🗿 = rockManager.getCollisionWith(🗡️);
			for (auto& 🗿 : 🗿🗿🗿) {
				if (markedRocks.count(🗿) != 0) continue;
				markedRocks.insert(🗿);

				🗿->health -= damage;
				if ( 🗿->health <= 0 ) {
					if( 🗿->timer == -1) {
						🗿->timer = 7;
					}
				}
			}
		} else { /* is not attacking */
			markedRocks.clear();
		}
		/* play animation and break rock and show exit */
		unsigned int scoreModify;
		bool isExitRock = rockManager.playBreakAnimation(testExit.position, &scoreModify);
		userInterface.alterScore(scoreModify);
		if ( isExitRock ) {
			testExit.SetShow();
		}
	} /* attack rock END */

	{ /* bomb rock BEGIN */ //FIXME: bombing area is slightly off

		if ( bombAnime.getFuse()==1 ) { /* is bombimg */

			const auto 🧨 = Rect::FromCenter(bombAnime.getCenter(), Vector2i(1,1) * TILE_SIZE * SCALE_SIZE);
			// Loop through all the rocks that collide with the bomb area
			const vector<Rock*> 🗿🗿🗿 = rockManager.getCollisionWith(🧨);
			for (auto& 🗿 : 🗿🗿🗿) {

				🗿->health -= damage;
				if ( 🗿->health <= 0 ) {
					if( 🗿->timer == -1) {
						🗿->timer = 7;
					}
				}
			}
		}
		/* play animation and break rock and show exit */
		unsigned int scoreModify;
		bool isExitRock = rockManager.playBreakAnimation(testExit.position, &scoreModify);
		userInterface.alterScore(scoreModify);
		if ( isExitRock ) {
			testExit.SetShow();
		}
	} /* bomb rock END */

	{ /* attack bug BEGIN */
		const auto p = bug.getPosition();
		bool isHitting =
			Rect::isOverlay(playerAttack.GetHitbox(), Rect::FromTopLeft(p, {50,50}))
			&& playerAttack.isShown();

		bug.setHit(isHitting);
		if ( isHitting ) { /* if isHitting */
			bug.alterHealth(-5);
		}
	} /* attack bug END */
	
	/* bomb fuse */
	if(bombAnime.getFuse()){
		bombAnime.update();
	}
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
				const Rect playerHitbox = player.GetHitbox();
				const auto pps = map.getPlaceablePositions();
				do { // FIXED: rock generate at player spawn point would break collision system
					rockManager.createRocksOn(pps);
				} while (rockManager.getHitbox().Collide(playerHitbox).size() != 0);
			}
			break;
		case 'N': //score--
		case 'M': //score++
			if(nChar=='N'){
				if(userInterface.getScore()){
					userInterface.alterScore(-1);
				}
			}
			else{
				userInterface.alterScore(1);
			}
			break;
		case 'B':
			if(bombAnime.getFuse()>0) break;
			bombAnime.useBomb(player.position,0);
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
			const Rect playerHitbox = player.GetHitbox();
			const Rect exitHitbox = testExit.GetHitbox();
			if (testExit.isShown() && Rect::isOverlay(playerHitbox, exitHitbox)) {
				// switch to next level
				if (!map.nextLevel()) // if no next level
					break;

				auto mapInfo = map.getInfo();
				SetupLevel(mapInfo);
			}
			break;
		case 'P': // player attack
			if(playerAttackTimer > 0) break; // cd-ing

			playerAttack.SetFrameIndexOfBitmap(
				getFrameIndexOfBitmapBy(attackDirection)
			);
			playerAttackTimer = PLAYER_ATTACK_TIME + PLAYER_ATTACK_CD;
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
	bombAnime.drawBomb();
	player.Draw();
	playerAttack.Draw();

	map.drawFront();
	
	bug.drawBug();
	
	userInterface.showUI();
	/* top layer */
}
