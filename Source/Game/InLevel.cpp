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
	BBC.LoadBitmapByString({"Resources/blackatom.bmp"},RGB(255,255,255));
	BBC.SetScale(SIZE_X);
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

	X.Init();

	uis.tb._bag = &bag;
	uis.rtui.setMoneyPtr(&bag._money);
}

void InLevel::OnBeginState()
{
	DEATH = false;
	map.setLevel(1);
	player.position = map.getInfo().startPosition * TILE_SIZE * SCALE_SIZE;

	bag._money = 0;

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

	if (playerStatus.health == 0) DEATH = true;
	if (DEATH) {
		player._sprite_player.SetShow(false);
	}
	
	// #define NO_COLLISION

	Vector2i moveVec = getMoveVecByKeys();
	if (DEATH) moveVec=Vector2i(0,0); // can't move bc it's daed
	if( moveVec!=Vector2i(0,0) ) { // is moving
		// player moving speed
		int speed = 0;
		{ /* running and tried BEGIN */
			const int highSpeed = 20;
			const int lowSpeed = 10;
			const int tiredSpeed = 5;
			speed = lowSpeed;
			if (isPress(VK_SHIFT)) { // run
				if (playerStatus.energy > 0) {
					speed = highSpeed;
					playerStatus.energy -= 0.4;
				} else {
					X.Play();
				}
			}
			if (playerStatus.energy <= 0) {
				speed = tiredSpeed;
			}
		} /* running and tried END */
		{ /* player move and collision BEGIN */
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
	}

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
			bag._money += scoreModify;
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

	// {
	// 	bool inLevel10 = map.getLevel() == 10u;
	// 	clint.inShop = inLevel10;
	// }
	isInTradingRoom = true;//map.getLevel() == 10; //FIXME: trading room
	uis.tb.setShowPrice(isInTradingRoom);
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
			rockManager.clear();
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
		case 'N': // money++
			bag._money += 10000;
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
			// } else if(Rect::isOverlay(player.GetHitbox(), dwarf.GetHitbox())) {
			// 	dwarf.trade();
			// } else if(Rect::isOverlay(player.GetHitbox(), gus.GetHitbox())) {
			// 	gus.trade();
			// }
			// /* ... */
			break;
		case 'L': /* kill bug */
			bug.alterHealth(-999);
			break;
	} /* switch (nChar) */
#endif /* DEBUG_KEY */

	if(DEATH) return; // can't control

	switch (nChar) { // attack and action(only enter exit for now)
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
			if(playerStatus.energy == 0) goto actionFailed;
			if( !player.canAttack() ) /* skip */;
			player.attack();
			playerStatus.energy -= 1.5;
			break;
	}
	/* trade and use items */
	#define CHERRY_BOMB_KEY '1'
	#define BOMB_KEY '2'
	#define MEGA_BOMB_KEY '3'
	#define FOOD_KEY '4'
	bool isTradingKeyPress = isPress(VK_SHIFT);
	if (isTradingKeyPress) { /* trading BEGIN */
		switch (nChar) {
			case CHERRY_BOMB_KEY:
				if(!isInTradingRoom) goto actionFailed;
				if(!bag.trade(Item::cherryBomb, 20)) goto actionFailed;
				break;
			case BOMB_KEY:
				if(!isInTradingRoom) goto actionFailed;
				if(!bag.trade(Item::Bomb, 80)) goto actionFailed;
				break;
			case MEGA_BOMB_KEY:
				if(!isInTradingRoom) goto actionFailed;
				if(!bag.trade(Item::megaBomb, 200)) goto actionFailed;
				break;
			case FOOD_KEY:
				if(!isInTradingRoom) goto actionFailed;
				if(!bag.trade(Item::Food, 40)) goto actionFailed;
				break;
			// actionFailed:
			// 	X.Play(); 
			// 	break;
		}
	} else { /* use item BEGIN */
		switch (nChar) {
			case CHERRY_BOMB_KEY:
				if(!bag.use(Item::cherryBomb)) goto actionFailed;
				if(bombAnime.getFuse()>0) goto actionFailed;
				bombAnime.useBomb(player.position,0);
				break;
			case BOMB_KEY:
				if(!bag.use(Item::Bomb)) goto actionFailed;
				if(bombAnime.getFuse()>0) goto actionFailed;
				bombAnime.useBomb(player.position,1);
				break;
			case MEGA_BOMB_KEY:
				if(!bag.use(Item::megaBomb)) goto actionFailed;
				if(bombAnime.getFuse()>0) goto actionFailed;
				bombAnime.useBomb(player.position,2);
				break;
			case FOOD_KEY:
				if(!bag.use(Item::Food)) goto actionFailed;
				playerStatus.energy += 40;
				playerStatus.health += 40;
				break;
			// actionFailed:
			// 	X.Play(); 
			// 	break;
		}
	} /* endif isTradingKeyPress */
	return;
/*
 * YES this is a GOTO LABEL only be used in this scope(OnKeyDown()),
 * because idk what's cpp goto statement ganna do.
 * anyway, this goto label help me a lot,
 * if you have any better idea plz fix it.
 */
actionFailed:
	X.Play(); 
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
	BBC.ShowBitmap();
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

	bombAnime.drawBigWhiteCover();
	
	for (auto oui : ouioui) {
		oui->Show();
	}
	/* top layer */
}
