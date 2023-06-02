#include "stdafx.h"

#include "ShopKeeper.h"

#include "../Config/config.h"
#include "../Config/scaler.h"

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
