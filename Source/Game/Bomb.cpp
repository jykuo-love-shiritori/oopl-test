#include "stdafx.h"
#include "Bomb.h"

#include "../Config/scaler.h"
#include "../Config/config.h"


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

	_bigWhiteCover.LoadBitmapByString({"Resources/whiteatom.bmp"},RGB(0,0,0));
    _bigWhiteCover.position = {0,0};
    _bigWhiteCover.SetScale(SIZE_X);
    _bigWhiteCover.SetShow();
}

void Bomb::useBomb(Vector2i placeLocation,int type){
    _sprite.position = placeLocation;
    _sprite.SetShow();
    if(type==0){
        _sprite.SetFrameIndexOfBitmap(0);
        _fuse=30;
        _blastRadius=1;
    }
    else if(type==1){
        _sprite.SetFrameIndexOfBitmap(1);
        _fuse=70;
        _blastRadius=4;
    }
    else{
        _sprite.SetFrameIndexOfBitmap(2);
        _fuse=110;
        _blastRadius=9;
    }
}

void Bomb::Update(){
    if(_fuse == 0) return;

    // anime start
    if(_fuse<10) _sprite.SetFrameIndexOfBitmap(_fuse);
    // big white cover
    _bigWhiteCover.SetShow(_fuse==5 || _fuse==4);
    // cd
    if(_fuse<3){_sprite.SetShow(false);}

    _fuse--;
}
