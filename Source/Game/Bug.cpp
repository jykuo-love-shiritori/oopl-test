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
	const auto origin = _currentMomentum.norm();
	_currentMomentum = (_currentMomentum + deltaVec/10).normalized() * deltaVec.norm() / 10;
	if (_currentMomentum.norm() < 20)
		_currentMomentum = _currentMomentum.normalized() * 20;
    _sprite.Move(_currentMomentum);
}