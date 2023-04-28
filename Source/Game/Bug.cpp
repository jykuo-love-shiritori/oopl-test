#include "stdafx.h"
#include "Bug.h"

#include "../Config/config.h"
#include "../Config/scaler.h"

void Bug::load() {
    _sprite.LoadBitmapByString({
        "Resources/bug.bmp"
    },RGB(255,255,255));
}

void Bug::init(Vector2i startLocation) {
    _currentMomentum = Vector2f(0,0);
    _health=22;
    _sprite.position=startLocation * TILE_SIZE * SCALE_SIZE;
}

void Bug::drawBug(){
    _sprite.Draw();
}

void Bug::pursuit(Vector2i playerLocation){
    Vector2f deltaVec=playerLocation-_sprite.position;
    const auto scaler = Vector2f(_currentMomentum).dot(deltaVec);
    const auto vec = (_currentMomentum+deltaVec).normalized();
    _currentMomentum = vec * scaler;
    _sprite.Move(_currentMomentum);
}