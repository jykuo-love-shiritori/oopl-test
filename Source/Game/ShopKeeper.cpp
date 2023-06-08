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
