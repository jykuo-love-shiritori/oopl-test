#include "stdafx.h"
#include "Rock.h"

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

bool Rock::createRockInstance(unsigned int tileID){
    for(int i=0;i<57;i++){
        if(tileID==_tilesAvailableForRocks[i]){
            double x=(double)std::rand()/(RAND_MAX+1.0);

            if(x>0.0){
                return true;
            }
            return false;
        }
    }
    return false;
}

game_framework::Bittermap Rock::getRockBMPs(){
    return _rockBMPs;
}

void Rock::createRocks(temp_name::Map map){
    for(int y=0;y < map.getMapSize().y ;y++){
		for (int x=0;x < map.getMapSize().x ;x++){
            int i=y*map.getMapSize().x+x;
			if(map.backTile[i]==0) continue;
            if(map.buildingTile[i]!=0 || map.frontTile[i]!=0) continue;
            if(createRockInstance(map.backTile[i])){
                _rockCoordinates.push_back({x,y});
            }
		}
	}
}

void Rock::drawRocks(){
    for(unsigned int i=0;i<_rockCoordinates.size();i++){
        _rockBMPs.SetFrameIndexOfBitmap(0);
        _rockBMPs.position = { _rockCoordinates[i].x * 16, _rockCoordinates[i].y * 16 };
        _rockBMPs.position = _rockBMPs.position * 4;
        _rockBMPs.Draw();
    }
}