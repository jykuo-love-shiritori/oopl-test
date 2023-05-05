#include "stdafx.h"
#include "RockManager.h"

#include "../Config/scaler.h"

#include <cstdlib> // for std::rand()
#include <vector>
#include <random>

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

        /* break animation */
        "Resources/Minerals/break0",
        "Resources/Minerals/break1",
        "Resources/Minerals/break2",
        "Resources/Minerals/break3",
        "Resources/Minerals/break4",
        "Resources/Minerals/break5",
        "Resources/Minerals/break6",
        "Resources/Minerals/break7",
        "Resources/Minerals/break8",
        "Resources/Minerals/break9"
    },RGB(255,255,255));  
}

int RockManager::rockSelector(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> res({300,300,30,20,15,1,3,3,5,5,3,5,3,1,3,5,3});
    return res(gen);
}

void RockManager::createRocksOn(const std::vector<Vector2i> placeablePositions) {
    clear();

    for(const Vector2i &pos : placeablePositions) {
        if ( 30 > std::rand() % 100 ) {
            Rock rock;
            rock.position = pos;
            rock.type = rockSelector();
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

std::vector<Rock*> RockManager::getCollisionWith(Rect hitbox) {
    std::vector<Rock*> vec = {};
    for (auto& rock : _rocks) {
        Rect rockBox = Rect::FromTopLeft(
				rock.position * TILE_SIZE * SCALE_SIZE,
                Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE
            );
        if(Rect::isOverlay(rockBox, hitbox)) {
            vec.push_back(&rock);
        }
    }
    vec.shrink_to_fit();
    return vec;
}

void RockManager::remove(std::set<Rock*> ptrs) {
    std::vector<Rock> newRocks = {};
    _hp = HitboxPool();
    for (auto& rock : _rocks) {
        if (ptrs.count(&rock) == 0) {
            newRocks.push_back(rock);
            // TODO: merge hitbox into rock struct
            _hp.AddHitbox( Rect::FromTopLeft(
				rock.position * TILE_SIZE * SCALE_SIZE,
                Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE
            ));
        }
    }
    _rocks = newRocks;
    _rocks.shrink_to_fit();
}

std::vector<Vector2i> RockManager::getPositions() const {
    std::vector<Vector2i> vec = {};
    for (const auto& rock : _rocks) {
        vec.push_back(rock.position *  TILE_SIZE * SCALE_SIZE);
    }
    vec.shrink_to_fit();
    return vec;
}
