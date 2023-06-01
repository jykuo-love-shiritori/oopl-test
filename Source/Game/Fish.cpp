#include "stdafx.h"
#include "Fish.h"
#include "../Config/config.h"
#include "../Config/scaler.h"
#define BOTTOM SIZE_Y-43
#define H_LEFT SIZE_X-83
#define E_LEFT SIZE_X-126
#define FULL_HEIGHT 143 

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

    _fish.SetHitBox({
        _fish.GetWidth(),
        _fish.GetHeight()
        });
	_greenbar.SetHitBox({
		_greenbar.GetWidth(),
		_greenbar.GetHeight()
		});

	srand(time(NULL));
	_fishposition = rand() % 100;
	_fish.SetTopLeft(527, 350+_fishposition);
	_greenbar.SetTopLeft(530, 320);
	_fishDone = false;
	_ispress = false;
	_process = 0;
	_fishprogress = 10;
	_fishMove = 0;
	_greenbarMove = 0;
	_fishstate = fishcolddown;
	_colddown = 0;
}


void Fish::fishReset() {
	_fishposition = rand() % 100;
	_fish.SetTopLeft(527, 350 + _fishposition);
	_greenbar.SetTopLeft(530, 320);
	_fishDone = false;
	_ispress = false;
	_process = 0;
	_fishprogress = 10;
	_fishMove = 0;
	_greenbarMove = 0;
	_colddown = 0;
}
void Fish::Update() {
	playercontrol();
	fishMove();
	_fish.SetTopLeft(527, 350 + _fishposition +_fishMove);
	_greenbar.SetTopLeft(530,320+_greenbarMove);
	fishOverlay();
	fishSuccess();
}
void Fish::fishKeyDown(bool ispress) {
	_ispress = ispress;
}
void Fish::playercontrol() {
	if (!_ispress && _greenbarMove <= 260 ) {
		_greenbarMove = _greenbarMove + 3;
		_unpresstime += 1;
		_presstime = 0;
	}
	else if (_ispress && _greenbarMove >= 0) {
		_greenbarMove = _greenbarMove + -3;
		_presstime += 1;
		_unpresstime = 0;
	}
}

void Fish::fishMove() {
	if (rand() % 2 ==0){
		if (_fishMove <= 260) _fishMove = _fishMove + 3;
	}
	else {
		if (_fishMove >= 0 ) _fishMove = _fishMove + -3;
	}
}
void Fish::fishOverlay() {
	if (game_framework::CMovingBitmap::IsOverlap(_fish, _greenbar)) {
		if (_fishprogress <= 300) _fishprogress += 1;
	}
	else {
		if (_fishprogress > 0) _fishprogress -= 1;
		if (_fishprogress == 0) _process -= 1;
		else _process = 0;
	}
}

void Fish::fishSuccess() {
	if (_fishprogress == 300) {
		_fishDone = true;
		_fishstate = fishsuccess;
	}
	else if (_process <= -30){
		_fishDone = true;
		_fishstate = fishfail;
	}
}

void Fish::showFish(){
	_FishGameFrame.SetTopLeft(500, 300);
	_FishGameFrame.ShowBitmap();
	for (int i = _fishprogress; i >0; --i) {
		_innerBar.SetTopLeft(565, 615 - i);
		_innerBar.ShowBitmap();
	}
	_greenbar.ShowBitmap();
	_fish.ShowBitmap();
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
}