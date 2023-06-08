#include "stdafx.h"

#include "ShopKeeper.h"

#include "../Config/config.h"
#include "../Config/scaler.h"

void ShopKeeper::init(Vector2f p) {
    const Vector2i regularBoxSize = Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE;
    
    _sprite.LoadBitmapByString({
        "resources/Clint.bmp",
    }, RGB(255, 255, 255));
    _sprite.SetScale(3);
    _sprite.SetHitBox(regularBoxSize * 0.7);
    _sprite.position = (Vector2i)(p);
    inShop=false;
}

// void MoneyShop::trade(Money* money, Bag* bag) {
//     auto minerals = bag.popMinerals();
//     for (auto m : minerals) {
//         money += m.value;
//     }
// }

void FoodShop::trade(int* money, Bag* bag, int type) {
    const int hotgodPrice = 50;
    if (*money >= hotgodPrice) {
        *money -= hotgodPrice;
        bag->append(Item::Food);
    }
}

void BombShop::trade(int* money, Bag* bag, int type) {
    const int bombPrice1 = 15;
    const int bombPrice2 = 50;
    const int bombPrice3 = 200;
    if(type==1){
        if (*money >= bombPrice1) {
            *money -= bombPrice1;
            bag->append(Item::cherryBomb);
        }
    }
    else if(type==2){
        if (*money >= bombPrice2) {
            *money -= bombPrice2;
            bag->append(Item::Bomb);
        }
    }
    else{
        if (*money >= bombPrice3) {
            *money -= bombPrice3;
            bag->append(Item::megaBomb);
        }
    }
}
