#include "stdafx.h"
#include "Bug.h"

#include "../Config/config.h"
#include "../Config/scaler.h"

void Bug::spawn(Vector2i startLocation){
    this->_health=22;
    this->_sprite.LoadBitmapByString({
        "Resources/bug.bmp"
    },RGB(255,255,255));
    this->_sprite.position=startLocation * TILE_SIZE * SCALE_SIZE;
}

void Bug::drawBug(){
    this->_sprite.Draw();
}

void Bug::pursuit(Vector2i playerLocation){
    Vector2i moveVec=(playerLocation-this->_sprite.position)/20;
    this->_sprite.Move(moveVec);
}