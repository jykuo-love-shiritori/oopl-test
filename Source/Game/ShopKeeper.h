#ifndef SHOP_KEEPER_H
#define SHOP_KEEPER_H

#include "./Bittermap.h"
#include "Bag.h"

#include "../Config/scaler.h"

class ShopKeeper {
    public:
        bool inShop;
        /* game misc things */
        void init(Vector2f p);
        void draw() {
            if ( ! inShop ) return;
            _sprite.Draw();
        }
        /* setter */
        void setPosition(Vector2f p) {
            _sprite.position = p;
        }

        /* getter */
		Rect GetHitbox() const { return _sprite.GetHitbox(); }

        /* methods */
        virtual void trade(int* money, Bag* bag, int type) = 0;
    private:
        game_framework::Bittermap _sprite;
};

class BombShop : public ShopKeeper {
public:
    void trade(int* money, Bag* bag, int type) override;
};

class FoodShop : public ShopKeeper {
public:
    void trade(int* money, Bag* bag, int type) override;
};

#endif /* SHOP_KEEPER_H */
