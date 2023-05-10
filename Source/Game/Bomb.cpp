#include "stdafx.h"
#include "Bomb.h"

#include "../Config/scaler.h"


void Bomb::init(){
    _sprite.LoadBitmapByString({
        "./Resources/Bomb/cherryBomb.bmp",
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
    _sprite.SetFrameIndexOfBitmap(0);
    _sprite.SetShow();
    if(type==0){_fuse=28;}
    else if(type==1){_fuse=68;}
    else{_fuse=108;}
}

void Bomb::update(){
    if(_fuse<8) _sprite.SetFrameIndexOfBitmap(_fuse);
    _fuse--;
    if(_fuse==0){_sprite.SetShow(false);}
}

void Bomb::drawBomb(){
    _sprite.Draw();
}