#include "stdafx.h"
#include "Fish.h"
#include "../Config/config.h"
#include "../Config/scaler.h"
#define FishFrame_POS_X SIZE_X - 900
#define FishFrame_POS_Y SIZE_Y - 600

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
	_ispress = false;
	_process = 0;
	_QteTime = 10;
	_fishstate = fishcolddown;
	_colddown = 0;
	_infishgame = false;
}


void Fish::fishReset(Vector2i pos) {
	_fish.position = pos + Vector2i(-175,150);
	_greenbar.position = pos + Vector2i(-175, 150);
	_ispress = false;
	_process = 0;
	_QteTime = 10;
	_colddown = 0;
}
void Fish::Update() {
	if (_infishgame){
		playercontrol();
		fishMove();
		fishOverlay();
		FishResult();
	}
	else if (_fishstate==fishcolddown){
		fishgameColddown();
	}
}
void Fish::fishKeyDown(bool ispress) {
	_ispress = ispress;
}
void Fish::playercontrol() {
	if (!_ispress /*&& _greenbar.position.y <= FishFrame_POS_Y*/) {
		_greenbar.Move(Vector2i(0, 3));
	}
	else if (_ispress /*&& _greenbar.position.y >= FishFrame_POS_Y - 260*/) {
		_greenbar.Move(Vector2i(0, -3));
	}
}
void Fish::fishMove(){
	if (rand() % 2 == 0) {
		if (_fish.position.y /*<= FishFrame_POS_Y*/)
			_fish.Move(Vector2i(0, 3));
	}
	else {
		if (_fish.position.y /*>= FishFrame_POS_Y - 260*/) 
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
		_infishgame = false;
		_fishsuccess = true;
		_fishstate = fishcolddown;
	}
	else if (_process <= -30){
		_fishsuccess = false;
		_fishstate = fishcolddown;
		_infishgame = false;
	}
}

void Fish::showFish(){
	if (_infishgame ==true) {
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
	if (_colddown>=30){
		_fishstate = fishReady;
	}
}

bool Fish::isFishKeyDown() {
	return _ispress;
}

void Fish::SetinFishGame(bool ingame) {
	_infishgame = ingame;
}
bool Fish::isInFishGame() {
	return _infishgame;
}
bool Fish::GetFishSuccess() {
	return _fishsuccess;
}