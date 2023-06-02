#include "stdafx.h"

#include "ShopKeeper.h"

#include "../Config/config.h"
#include "../Config/scaler.h"

void ShopKeeper::init() {
    const Vector2i regularBoxSize = Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE;
    
    _sprite.LoadBitmapByString({
        "resources/Clint.bmp",
    }, RGB(255, 255, 255));
    _sprite.SetScale(1);
    _sprite.SetHitBox(regularBoxSize * 0.7);
}

// void MoneyShop::trade(Money* money, Bag* bag) {
//     auto minerals = bag.popMinerals();
//     for (auto m : minerals) {
//         money += m.value;
//     }
// }

void FoodShop::trade(int* money, Bag* bag) {
    const int hotgodPrice = 400;
    if (*money >= hotgodPrice) {
        *money -= hotgodPrice;
        bag->append(Item::Food);
    }
}

void BombShop::trade(int* money, Bag* bag) {
    const int bombPrice1 = 15;
    const int bombPrice2 = 50;
    const int bombPrice3 = 200;
    if (*money >= bombPrice1) {
        *money -= bombPrice1;
        bag->append(Item::Bomb);
    }
}
