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
    _currentMomentum=_currentMomentum.normalized();
}

void Bug::drawBug(){
    _sprite.Draw();
}

void Bug::pursuit(Vector2i playerLocation){
    Vector2f deltaVec=playerLocation-_sprite.position;
    _currentMomentum=_currentMomentum+deltaVec.normalized();
    _sprite.Move(_currentMomentum);
}