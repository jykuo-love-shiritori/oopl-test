#include "stdafx.h"
#include "Bomb.h"

#include "../Config/scaler.h"


void Bomb::init(int type){
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

    if(type==0){
        _blastRadius=3;
        _damage=5;
        _fuse=28;
    }
    else if(type==1){
        _blastRadius=5;
        _damage=10;
        _fuse=48;
    }
    else if(type==2){
        _blastRadius=8;
        _damage=15;
        _fuse=68;
    }
}

void Bomb::useBomb(Vector2i playerLocation){
    _position=playerLocation * TILE_SIZE * SCALE_SIZE;
    _sprite.SetShow();
    if(_fuse>0){
        if(_fuse<8) _sprite.SetFrameIndexOfBitmap(_fuse);
        _fuse--;
    }
}

void Bomb::drawBomb(){
    _sprite.Draw();
}