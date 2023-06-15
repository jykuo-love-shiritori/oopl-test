#include "stdafx.h"
#include "Fish.h"
#include "../Config/config.h"
#include "../Config/scaler.h"
#define FishFrame_POS_X SIZE_X - 900
#define FishFrame_POS_Y SIZE_Y - 600
#define init_POS_Y -130
#define init_POS_X -170

void Fish::init(){
    _fish.LoadBitmapByString({
        "./Resources/Fishing/FishBait.bmp" },RGB(0,0,0));
	_fish.SetScale(0.5);
	_greenbar.LoadBitmapByString({
		"./Resources/Fishing/FishLimitArea.bmp" }, RGB(0, 0, 0));
	_greenbar.SetScale(0.8);
	_FishGameFrame.LoadBitmapByString({
		"./Resources/Fishing/FishGameFrame.bmp" }, RGB(0, 0, 0));
	_FishGameFrame.SetScale(1.2);
	_innerBar.LoadBitmapByString({
		"resources/barInner.bmp"
		}, RGB(0, 0, 0));
	_innerBar.SetScale(1.0);
	_fishstate = fishReady;
	_colddown = 2; // skip 1, bc colddown 1 makes fishstate true
}


void Fish::fishReset(Vector2i pos) {
	_fish.position = pos + Vector2i(init_POS_X,init_POS_Y+rand()%200);
	_greenbar.position = pos + Vector2i(init_POS_X, init_POS_Y);
	_fishRange = pos.y +init_POS_Y;
	_ispress = false;
	_process = 0;
	_QteTime = 5;
	_colddown = 0;
}
void Fish::Update() {
	switch (_fishstate)
	{
	case infish:
		playercontrol();
		fishMove();
		fishOverlay();
		FishResult();
		break;
	case fishcolddown:
		fishgameColddown();
	}
}
void Fish::fishKeyDown(bool ispress) {
	_ispress = ispress;
}
void Fish::playercontrol() {
	if (!_ispress && _greenbar.position.y <= _fishRange+260) {
		_greenbar.Move(Vector2i(0, 3));
	}
	else if (_ispress && _greenbar.position.y >= _fishRange) {
		_greenbar.Move(Vector2i(0, -3));
	}
}
void Fish::fishMove(){
	if (rand() % 2 == 0) {
		if (_fish.position.y <= _fishRange + 260)
			_fish.Move(Vector2i(0, 3));
	}
	else {
		if (_fish.position.y >= _fishRange)
			_fish.Move(Vector2i(0, -3));
	}
}
void Fish::fishOverlay() {
	if (game_framework::CMovingBitmap::IsOverlap(_fish, _greenbar)) {
		if (_QteTime <= 300) _QteTime += 1;
	}
	else {
		if (_QteTime > 0) _QteTime -= 1;
		if (_QteTime == 0) _process -= 1;
		else _process = 0;
	}
}

void  Fish::FishResult() {
	if (_QteTime == 300) {
		_fishsuccess = true;
		_fishstate = fishcolddown;
	}
	else if (_process <= -60){
		_fishsuccess = false;
		_fishstate = fishcolddown;
	}
}

void Fish::showFish(){
	if (_fishstate == infish) {
		_FishGameFrame.SetTopLeft(FishFrame_POS_X,FishFrame_POS_Y);
		_FishGameFrame.ShowBitmap();
		for (int i = _QteTime; i > 0; --i) {
			_innerBar.SetTopLeft(SIZE_X - 835, SIZE_Y - 285 - i);
			_innerBar.ShowBitmap();
		}
		_greenbar.Draw();
		_fish.Draw();
	}
}

void Fish::SetFishState(int state) {
	_fishstate = state;
}
int Fish::GetFishState() {
	return _fishstate;
}
int Fish::GetFishColddown() {
	return _colddown;
}
void Fish::fishgameColddown() {
	_colddown += 1;
	if (_colddown>=50){
		_fishstate = fishReady;
	}
}

bool Fish::isFishKeyDown() {
	return _ispress;
}

bool Fish::GetFishSuccess() {
	return _fishsuccess;
}