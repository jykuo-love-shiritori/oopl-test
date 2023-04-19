#include "stdafx.h"
#include "Bug.h"

#include "../Config/config.h"
#include "../Config/scaler.h"

void Bug::spawn(Vector2i startLocation,Vector2i playerLocation){
    _health=22;
    _sprite.LoadBitmapByString({
        "Resources/bug.bmp"
    },RGB(255,255,255));
    _sprite.position=startLocation * TILE_SIZE * SCALE_SIZE;
    _currentMomentum=playerLocation-_sprite.position;
    _currentMomentum=_currentMomentum*7/sqrt(pow((_currentMomentum.x),2)+pow((_currentMomentum.y),2));
}

void Bug::drawBug(){
    _sprite.Draw();
}

void Bug::pursuit(Vector2i playerLocation){
    Vector2i deltaVec=playerLocation-_sprite.position;
    _currentMomentum=_currentMomentum+deltaVec*3/100;
    _sprite.Move(_currentMomentum);
}