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
#include <functional>

#include "../Config/keymap.h"
#include "../Config/scaler.h"
#include "../Config/Debug.h"

using namespace game_framework;
using namespace game_framework::stage;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

InLevel::InLevel(CGame *g) : CGameState(g), 🐼Proxy(🐼, false)
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
	🐼.load();
	// use bind to get the function for Covallo
	🐼.init(
	  {0, 0},
	  std::bind(&Player::GotHit, &player ,std::placeholders::_1), 
	  std::bind(&RockManager::getCollisionWith, &rockManager, std::placeholders::_1),
	  &map.hp,
	  true, /*            autoAttack position v */
	  true, /*follow position > */ &player.position);
	
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

	fishgame.init();
	uis.tb._bag = &bag;
	uis.rtui.setMoneyPtr(&bag._money);

	mp5->Load(0,"Resources/Audio/brrrrr.mp3");
	mp5->Load(1,"Resources/Audio/mineBGM.mp3");
	mp5->Load(2,"Resources/Audio/stoneCrack1.wav");
	mp5->Load(3,"Resources/Audio/stoneCrack2.wav");
	mp5->Load(4,"Resources/Audio/bombFuse.mp3");
	mp5->Load(5,"Resources/Audio/Determination.mp3");

	resultScreen.LoadBitmapByString({
		"Resources/resultScreenBG.bmp",
		"Resources/resultScreen.bmp",
		"Resources/finalScoreText.bmp"
	},RGB(255,255,255));
}

void InLevel::OnBeginState()
{
	DEATH = false;
	flag=false;
	mp5->Stop(5);
	map.setLevel(1);
	player.position = map.getInfo().startPosition * TILE_SIZE * SCALE_SIZE;
	player._sprite_player.SetShow();

	bag.reset();

	auto mapInfo = map.getInfo();
	SetupLevel(mapInfo);

	bug.init(Vector2i(100,100));

	playerStatus.health=100;
	playerStatus.energy=100;

	mp5->Play(1,true);
	🐼Proxy.SetEnable(false);
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
	const auto ps = map.getPlaceablePositions();
	// set position(random placeable position) when enter new level
	🐼.setPosition(ps[rand() % static_cast<int>(ps.size())] * TILE_SIZE * SCALE_SIZE);
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

void InLevel::GameOver(){
	resultScreen.SetScale(2);
	resultScreen.SetTopLeft(0,0);
	resultScreen.SetFrameIndexOfBitmap(0);
	resultScreen.Show();

	resultScreen.SetScale(1.5);
	resultScreen.SetCenter(SIZE_X/2,SIZE_Y/4);
	resultScreen.SetFrameIndexOfBitmap(1);
	resultScreen.Show();

	resultScreen.SetScale(1);
	resultScreen.SetCenter(SIZE_X/2,SIZE_Y/3);
	resultScreen.SetFrameIndexOfBitmap(2);
	resultScreen.Show();

	Digit finalScore =  Digit(&bag._money, 3);
	finalScore.lsb_location={SIZE_X/2,SIZE_Y/2};
	finalScore.Show();
}

void InLevel::OnMove()							// 移動遊戲元素
{
	//TODO: can change timer into cool thing
	// unsigned int deltaTime = CSpecialEffect::GetEllipseTime();
	// CSpecialEffect::SetCurrentTime();

	if (playerStatus.health == 0) DEATH = true;
	if (DEATH) {
		if (flag) return;
		flag = true;
		player._sprite_player.SetShow(false);
		mp5->Stop(1);
		mp5->Play(5,true);
		GameOver();
		return;
	}
	
	// #define NO_COLLISION

	Vector2i moveVec = getMoveVecByKeys();
	const HitboxPool collisionPool = map.hp + rockManager.getHitbox();
	if (DEATH) moveVec=Vector2i(0,0); // can't move bc it's daed
	if( moveVec!=Vector2i(0,0) ) { // is moving
		// player moving speed
		int speed = 0;
		{ /* running and tried BEGIN */
			const int highSpeed = 15;
			const int lowSpeed = 10;
			const int tiredSpeed = 5;
			speed = lowSpeed;
			if (isPress(VK_SHIFT)) { // run
				if (playerStatus.energy > 0) {
					speed = highSpeed;
					playerStatus.energy -= 0.2;
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

			for (int i = 0; i < speed; i++) {
				#ifndef NO_COLLISION
				player.MoveWithCollision(moveVec, collisionPool);
				#else /* NO_COLLISION */
				player.Move(moveVec);
				#endif /* NO_COLLISION */
			}
			// move all Cavallo things with collision
		} /* player move and collision END */
	} // endif is moving

	🐼Proxy.Invoke(&Cavallo::move, Unity::HitboxPool(collisionPool));
	playerStatus.health -= player.🔫💥 * 0.5;
	player.🔫💥 = 0;
	player.Update();

	// Damage value caused by the attack. //FIXME: and bomb
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
					🗿->health -= 1;
					if(std::rand()%2==0){mp5->Play(2);}
					else{mp5->Play(3);}
				}
			} else { /* is not attacking */
				markedRocks.clear();
			}
		} /* attack rock END */
		{ /* bomb rock BEGIN */ //FIXME: bombing area is slightly off
			if ( bombAnime.getFuse()==3 ) { /* is bombing */
				const auto 🧨 = Rect::FromCenter(bombAnime.getCenter(), Vector2i(1,1) * bombAnime.getBlastRadius() * TILE_SIZE * SCALE_SIZE);
				if(Rect::isOverlay(player.getHitBox(),🧨)){
					playerStatus.health-=bombAnime.getDamage()*5;
				}
				if(Rect::isOverlay(bug.GetHitbox(),🧨)){
					bug.alterHealth(-bombAnime.getDamage()*10);
				}
				// Enumerate all the rocks that collide with the bomb area
				const vector<Rock*> 🗿🗿🗿 = rockManager.getCollisionWith(🧨);
				for (auto& 🗿 : 🗿🗿🗿) {
					🗿->health -= bombAnime.getDamage();
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

	isInTradingRoom = map.getLevel() == 10; //FIXED: trading room
	uis.tb.setShowPrice(isInTradingRoom);

	fishgame.fishKeyDown(isPress('Z'));
	fishgame.Update();
	//when enter colddown get FishGame result 
	if (fishgame.GetFishColddown() == 1){
		if (fishgame.GetFishSuccess()){
			bag._money += 5;
		}
		else {
			bag._money -= 2;
		}
	}
}

void InLevel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
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

#ifdef RESPAWN_ROCKS_DEBUG_KEY
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
#endif /* RESPAWN_ROCKS_DEBUG_KEY*/


#ifdef ADD_MONEY_DEBUG_KEY
		case 'N': // money++
			bag._money += 10000;
			break;
#endif /* ADD_MONEY_DEBUG_KEY */

#ifdef CHERRY_BOMB_DEBUG_KEY
		case 'B': /* place cherry bomb */
			bombAnime.useBomb(player.position,0);
			break;
#endif /* CHERRY_BOMB_DEBUG_KEY */	

#ifdef SPAWN_LADDER_DEBUG_KEY
		case 'E': // randomly create exit
			{
				testExit.SetShow();
				auto pps = map.getPlaceablePositions();
				testExit.position = pps[std::rand()%pps.size()] * TILE_SIZE * SCALE_SIZE;
			}
			break;
#endif /* SPAWN_LADDER_DEBUG_KEY */

#ifdef ELEVATOR
		case 'E': // go to trade room
			{
				static auto wasAt = -1;
				if(wasAt == -1 || map.getLevel() != 10) {
					wasAt = map.getLevel();
					map.setLevel(10);
				} else {
					map.setLevel(wasAt);
					wasAt = -1;
				}
				rockManager.clear();
				SetupLevel(map.getInfo());
			}
			break;
#endif /* ELEVATOR */

#ifdef RESTART_DEBUG_KEY
		case 'R': /* BACK TO START SCREEN */
			mp5->Stop(1);
			mp5->Stop(5);
			GotoGameState(GAME_STATE_INIT);
			break;
#endif /* RESTART_DEBUG_KEY */

#ifdef ADD_HEALTH_DEBUG_KEY
		case 'H':
			playerStatus.health += 20;
			break;
#endif /* ADD_HEALTH_DEBUG_KEY */

#ifdef KILL_BUG_DEBUG_KEY
		case 'L': /* kill bug */
			bug.alterHealth(-999);
			break;
#endif /* KILL_BUG_DEBUG_KEY */
	} /* switch (nChar) */

#endif /* DEBUG_KEY */

	if(DEATH) return; // can't control

	// FISHING
	if (nChar=='Z'){ //when press other key stop fish game
		if(bag._money < 2) goto actionFailed;
		if (fishgame.GetFishState()==Fish::fishReady){
			//when FishGame not start, press z init and start fishgame
			fishgame.fishReset(player.position);
			fishgame.SetFishState(Fish::infish);
		}
	}
	else {
		fishgame.SetFishState(Fish::fishcolddown);
	}

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
			if( !player.canAttack() ) break;/* skip */;
			player.attack();
			mp5->Play(0);
			playerStatus.energy -= 1;
			break;
		case 'Q': // go to game over
			playerStatus.health=0;
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
	static string s = "";
	s += static_cast<char>(nChar);
	if (s.size() > 7) {
		s = s.substr(1, 7);
	}
	if (s == "CAVALLO") {
		🐼Proxy.SetEnable(true);
	}
	if (s == "DISABLE") {
		🐼Proxy.SetEnable(false);
	}
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
void InLevel::OnMButtonDown(UINT nFlags, CPoint point)
{
	point.x = point.x + Bittermap::CameraPosition->x - SIZE_X / 2;
	point.y = point.y + Bittermap::CameraPosition->y - SIZE_Y / 2;
	// set destination of Cavallo when click mouse wheel (for not follow mode)
	🐼Proxy.Invoke(&Cavallo::setDest, Vector2i( point.x, point.y ));
}
void InLevel::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) {
	point.x = point.x + Bittermap::CameraPosition->x - SIZE_X / 2;
	point.y = point.y + Bittermap::CameraPosition->y - SIZE_Y / 2;
	if (!🐼.isAutoAttack() && zDelta < 0) {
		// if not auto attack throw bomb to mouse position
		🐼Proxy.Invoke(&Cavallo::Throw, Vector2f(static_cast<float>(point.x), static_cast<float>(point.y)));
	}

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
	BBC.ShowBitmap();
	
	map.drawBack();
	map.drawBuilding();

	rockManager.drawRocks();
	testExit.Draw();
	bombAnime.drawBomb();
	player.Draw();

	X.Show();
	// draw Cavallo and its things sprites
	🐼Proxy.Invoke(&Cavallo::draw);

	map.drawFront();
	
	bug.drawBug();

	bombAnime.drawBigWhiteCover();
	
	fishgame.showFish();
	

	for (auto oui : ouioui) {
		oui->Show();
	}

	if(DEATH){
		GameOver();
	}
	/* top layer */
}
