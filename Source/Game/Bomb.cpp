#include "stdafx.h"
#include "Bomb.h"

#include "../Config/scaler.h"
#include "../Library/audio.h"


void Bomb::init(){
    _sprite.LoadBitmapByString({
        "./Resources/Bomb/cherryBomb.bmp",
        "./Resources/Bomb/bomb.bmp",
        "./Resources/Bomb/megaBomb.bmp",
        "./Resources/Bomb/50.bmp",
        "./Resources/Bomb/51.bmp",
        "./Resources/Bomb/52.bmp",
        "./Resources/Bomb/53.bmp",
        "./Resources/Bomb/54.bmp",
        "./Resources/Bomb/55.bmp",
        "./Resources/Bomb/56.bmp",
        "./Resources/Bomb/57.bmp"
    },RGB(0,0,0));
    _sprite.SetHitBox({
        _sprite.GetWidth(),
        _sprite.GetHeight()
        });

    _fuse=-1;
    _sprite.SetShow(false);
}

void Bomb::useBomb(Vector2i placeLocation,int type){
    _sprite.position = placeLocation;
    _sprite.SetShow();
    if(type==0){
        _sprite.SetFrameIndexOfBitmap(0);
        _fuse=50;
        _blastRadius=1;
        _damage=1;
    }
    else if(type==1){
        _sprite.SetFrameIndexOfBitmap(1);
        _fuse=80;
        _blastRadius=3;
        _damage=2;
    }
    else{
        _sprite.SetFrameIndexOfBitmap(2);
        _fuse=120;
        _blastRadius=6;
        _damage=3;
    }
	game_framework::CAudio::Instance()->Play(4);
}

void Bomb::Update(){
    if(_fuse != 0){
        if(_fuse<10) _sprite.SetFrameIndexOfBitmap(_fuse);
        _fuse--;
        if(_fuse<3){
			_sprite.SetShow(false);
			game_framework::CAudio::Instance()->Stop(4);
		}
	}
}

void Bomb::drawBomb(){
    _sprite.Draw();
}