#include "stdafx.h"
#include "Rock.h"

#include "../Config/scaler.h"

#include <cstdlib>

void Rock::load(){
    _rockBMPs.LoadBitmapByString({
        "Resources/Minerals/stoneType1.bmp",    //0
        "Resources/Minerals/stoneType2.bmp",    //1
        "Resources/Minerals/copperNode.bmp",    //2
        "Resources/Minerals/ironNode.bmp",      //3
        "Resources/Minerals/goldNode.bmp",      //4
        "Resources/Minerals/iridiumNode.bmp",   //5
        "Resources/Minerals/amethystNode.bmp",  //6
        "Resources/Minerals/topazNode.bmp",     //7
        "Resources/Minerals/quartz.bmp",        //8
        "Resources/Minerals/earthCrystal.bmp",  //9
        "Resources/Minerals/aquamarineNode.bmp",//10
        "Resources/Minerals/frozenTear.bmp",    //11
        "Resources/Minerals/jadeNode.bmp",      //12
        "Resources/Minerals/diamondNode.bmp",   //13
        "Resources/Minerals/emeraldNode.bmp",   //14
        "Resources/Minerals/fireQuartz.bmp",    //15
        "Resources/Minerals/rubyNode.bmp",      //16
    },RGB(255,255,255));  
}


int Rock::getHealth(){
    return _health;
}

int Rock::getType(){
    return _type;
}

game_framework::Bittermap Rock::getRockBMPs(){
    return _rockBMPs;
}

int Rock::rockSelector(){
    int res=std::rand()%1000;
    if(res<430) return stoneType1;
    else if(res<860) return stoneType2;
    else if(res<900) return copperNode;
    else if(res<925) return ironNode;
    else if(res<940) return goldNode;
    else if(res<941) return iridiumnNode;
    else if(res<945) return amethystNode;
    else if(res<949) return topazNode;
    else if(res<955) return quartz;
    else if(res<965) return earthCrystal;
    else if(res<969) return aquamarineNode;
    else if(res<979) return frozenTear;
    else if(res<983) return jadeNode;
    else if(res<985) return emeraldNode;
    else if(res<990) return diamondNode;
    else if(res<996) return fireQuartz;
    else return rubyNode;
}

void Rock::createRocks(const temp_name::Map map){
    /* init */
    _rockTypes = {};
    _rockCoordinates={};
    hp = HitboxPool();

    for(const Vector2i &pos : map.getPlaceablePositions()) {
        if ( 30 > std::rand() % 100 ) {
            _rockCoordinates.push_back(pos);
            _rockTypes.push_back(rockSelector());
            hp.AddHitbox( Rect::FromTopLeft(
				pos * TILE_SIZE * SCALE_SIZE,
                Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE
            ));
        }
    }
}

void Rock::drawRocks(){
    for(unsigned int i=0;i<_rockCoordinates.size();i++){
        _rockBMPs.SetFrameIndexOfBitmap(_rockTypes[i]);
        // _rockBMPs.SetFrameIndexOfBitmap(std::rand() % 17); //disco party
        _rockBMPs.position = _rockCoordinates[i] * TILE_SIZE * SCALE_SIZE;
        _rockBMPs.Draw();
    }
}