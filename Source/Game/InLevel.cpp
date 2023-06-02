#include "Item.h"
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
#include "../Config/Debug.h"

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
	
	player.Init();

	map.loadBMPs(datapath);
	map.bmps.SetScale(SCALE_SIZE);

	map.setLevel(1);

	for (auto oui : ouioui) {
		oui->Init();
	}

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
	uis.eh.setHealth(&playerStatus.health);
	uis.eh.setEnergy(&playerStatus.energy);

	X.LoadBitmapByString({"Resources/x.bmp"}, RGB(31,31,31));

	uis.tb._bag = &bag;
}

void InLevel::OnBeginState()
{
	map.setLevel(1);
	player.position = map.getInfo().startPosition * TILE_SIZE * SCALE_SIZE;

	uis.rtui.setScore(0);

	auto mapInfo = map.getInfo();
	SetupLevel(mapInfo);

	bug.init(Vector2i(100,100));

	playerStatus.health=100;
	playerStatus.energy=100;
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
	bug.init(Vector2i(1000,1000));
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
		// Update player facing
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

	player.Update();

	// Damage value caused by the attack. //FIXME: and bomb
	const int damage = 1;
	{ /* break rock BEGIN */
		{ /* attack rock BEGIN */
			// A static set can be used to keep track of marked rocks until the end of the round of attack
			static std::set<Rock*> markedRocks = {};

			if ( player.isAttacking() ) { /* is attacking */
				const auto 🗡️ = player.getAttackBox();
				// Enumerate all the rocks that collide with the attack area
				const vector<Rock*> 🗿🗿🗿 = rockManager.getCollisionWith(🗡️);
				for (auto& 🗿 : 🗿🗿🗿) {
					if (markedRocks.count(🗿) != 0) continue;
					markedRocks.insert(🗿);
					🗿->health -= damage;
				}
			} else { /* is not attacking */
				markedRocks.clear();
			}
		} /* attack rock END */
		{ /* bomb rock BEGIN */ //FIXME: bombing area is slightly off
			if ( bombAnime.getFuse()==3 ) { /* is bombing */
				const auto 🧨 = Rect::FromCenter(bombAnime.getCenter(), Vector2i(1,1) * bombAnime.getBlastRadius() * TILE_SIZE * SCALE_SIZE);
				// Enumerate all the rocks that collide with the bomb area
				const vector<Rock*> 🗿🗿🗿 = rockManager.getCollisionWith(🧨);
				for (auto& 🗿 : 🗿🗿🗿) {
					🗿->health -= damage;
				}
			}
		} /* bomb rock END */
		{ /* play animation and break rock and show exit */
			unsigned int scoreModify;
			bool isExitRock = rockManager.playBreakAnimation(testExit.position, &scoreModify);
			uis.rtui.alterScore(scoreModify);
			if ( isExitRock ) {
				testExit.SetShow();
			}
		}
	} /* break rock END */

	if ( bug.isAlive() ) { /* bug update BEGIN */
		bug.pursuit(player.position);
		{ /* bug collide player BEGIN */
			//player.SetFrameIndexOfBitmap(0);
			if ( Rect::isOverlay(player.getHitBox(), bug.GetHitbox() ))
			{
				//player.SetFrameIndexOfBitmap(1);
				playerStatus.health -= 0.5;
			}
		} /* bug collide player END */
		{ /* player attack bug BEGIN */
			bool isHitting =
				Rect::isOverlay(player.getAttackBox(), bug.GetHitbox())
				&& player.isAttacking();

			bug.setHit(isHitting);
			if ( isHitting ) { /* if isHitting */
				bug.alterHealth(-5);
			}
		} /* player attack bug END */
	} /*bug update END */
	
	for (auto u : skillOrAnime) {
		u->Update();
	}

	//FIXME: easy for modify
	if (playerStatus.health < 0 ) playerStatus.health = 0;
	if (playerStatus.energy < 0 ) playerStatus.energy = 0;
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
//#define DEBUG_KEY
#ifdef DEBUG_KEY

	int mapIndex = (int)map.getLevel();
	switch (nChar) {
#ifdef JUMP_LEVEL_DEBUG_KEY
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
#endif /* JUMP_LEVEL_DEBUG_KEY */
		case 'O': // randomly create/clear rock
			if(isPress(VK_SHIFT)){
				rockManager.clear();
			} else {
				const Rect playerHitbox = player.getHitBox();
				const auto pps = map.getPlaceablePositions();
				do { // FIXED: rock generate at player spawn point would break collision system
					rockManager.createRocksOn(pps);
				} while (rockManager.getHitbox().Collide(playerHitbox).size() != 0);
			}
			break;
		case 'N': //score--
		case 'M': //score++
			if(nChar=='N'){
				if(uis.rtui.getScore()){
					uis.rtui.alterScore(-1);
				}
			}
			else{
				uis.rtui.alterScore(100);
			}
			break;
		case 'B': /* place cherry bomb */
			bombAnime.useBomb(player.position,0);
			break;
#ifdef SPAWN_LADDER
		case 'E': // randomly create exit
			{
				testExit.SetShow();
				auto pps = map.getPlaceablePositions();
				testExit.position = pps[std::rand()%pps.size()] * TILE_SIZE * SCALE_SIZE;
			}
			break;
#endif /* SPAWN_LADDER */
#ifdef ELEVATOR
		case 'E': // randomly create exit
			{
				static auto wasAt = -1;
				if(wasAt == -1) {
					wasAt = map.getLevel();
					map.setLevel(10);
				} else {
					map.setLevel(wasAt);
					wasAt = -1;
				}
				rockManager.clear();
				player.position = map.getInfo().startPosition * TILE_SIZE * SCALE_SIZE;
			}
			break;
#endif /* ELEVATOR */
		case 'R': /* BACK TO START SCREEN */
			GotoGameState(GAME_STATE_INIT);
			break;
		case 'H':
			playerStatus.health += 20;
			break;
		case 'T': /* buy bomb */
			if(true) { // FIXME: need to determine whether there is a shop
				auto m = uis.rtui.getScore();
				clint.trade(&m, &bag);
				uis.rtui.setScore(m);
			}
			// } else if(Rect::isOverlay(player.GetHitbox(), dwarf.GetHitbox())) {
			// 	dwarf.trade();
			// } else if(Rect::isOverlay(player.GetHitbox(), gus.GetHitbox())) {
			// 	gus.trade();
			// }
			// /* ... */
			break;
		case 'F': /* bug and eat food */
			if(true) { // FIXME: need to determine whether there is a shop
				auto m = uis.rtui.getScore();
				gus.trade(&m, &bag);
				uis.rtui.setScore(m);
			}
			if(!bag.use(Item::Food)){
				X.Play();
				break;
			}
			playerStatus.energy += 400;
			playerStatus.health += 400;
			break;
	} /* switch (nChar) */
#endif /* DEBUG_KEY */

	switch (nChar) {
		case KEY_DO_ACTION: // Check/Do Action
			const Rect playerHitbox = player.getHitBox();
			const Rect exitHitbox = testExit.GetHitbox();
			if (testExit.isShown() && Rect::isOverlay(playerHitbox, exitHitbox)) {
				// switch to next level
				if (!map.nextLevel()) // if no next level
					break;

				auto mapInfo = map.getInfo();
				SetupLevel(mapInfo);
			}
			// static unsigned int enterFloor = -1;
			// if (phase == 10 && Rect::isOverlay(playerHitbox, exitHitbox))
			break;
		case 'P': // player attack
			if(playerStatus.energy == 0){
				X.Play();
				break;
			}
			if( player.canAttack() ) {
				player.attack();
				playerStatus.energy -= 1.5;
			}
			break;
		case '1':
		case '2':
		case '3':
			if(isPress(VK_SHIFT)){
				if(true) { // FIXME: need to determine whether there is a shop
				auto m = uis.rtui.getScore();
				clint.trade(&m, &bag);
				uis.rtui.setScore(m);
				}
				break;
			}
			if(!bag.use(Item::Bomb)){
				X.Play();
				break;
			}
			if(bombAnime.getFuse()>0) break;
			if(nChar=='1'){bombAnime.useBomb(player.position,0);}
			if(nChar=='2'){bombAnime.useBomb(player.position,1);}
			if(nChar=='3'){bombAnime.useBomb(player.position,2);}
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
	X.Show();

	map.drawFront();
	
	bug.drawBug();
	
	for (auto oui : ouioui) {
		oui->Show();
	}
	/* top layer */
}
