#include "stdafx.h"
#include "RockManager.h"

#include "../Config/scaler.h"

#include <cstdlib> // for std::rand()
#include <vector>

void RockManager::loadBMP(){
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

void RockManager::createRocksOn(const std::vector<Vector2i> placeablePositions) {
    clear();

    for(const Vector2i &pos : placeablePositions) {
        // TODO: change to new rarity function
        if ( 0.2 > (double)std::rand()/(RAND_MAX+1.0)) {
            Rock rock;
            rock.position = pos;
            rock.type = std::rand()%17;
            _rocks.push_back(rock);
            _hp.AddHitbox( Rect::FromTopLeft(
				pos * TILE_SIZE * SCALE_SIZE,
                Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE
            ));
        }
    }

    _rocks.shrink_to_fit();
}

void RockManager::drawRocks() const{
    for (Rock const& rock : _rocks) {
        // _rockBMPs.SetFrameIndexOfBitmap(std::rand() % 17); //disco party
        _rockBMPs.Draw(
            rock.position * TILE_SIZE * SCALE_SIZE,
            rock.type
        );
    }
}

HitboxPool RockManager::getHitbox() const {
    return _hp;
}

void RockManager::clear() {
    _rocks.clear();
    _hp = HitboxPool();
}