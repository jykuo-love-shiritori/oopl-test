#ifndef SHOP_KEEPER_H
#define SHOP_KEEPER_H

#include "./Bittermap.h"
#include "Bag.h"

#include "../Config/scaler.h"

class ShopKeeper {
    public:
        /* game misc things */
        void init();
        void draw() {_sprite.Draw();}

        /*getter */
		Rect GetHitbox() const { return _sprite.GetHitbox(); }

        /* methods */
        virtual void trade(int* money, Bag* bag) = 0;
    private:
        game_framework::Bittermap _sprite;
};

class BombShop : public ShopKeeper {
public:
    void trade(int* money, Bag* bag) override;
};

class FoodShop : public ShopKeeper {
public:
    void trade(int* money, Bag* bag) override;
};

#endif /* SHOP_KEEPER_H */
