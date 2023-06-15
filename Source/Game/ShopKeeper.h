#ifndef SHOP_KEEPER_H
#define SHOP_KEEPER_H

#include "./Bittermap.h"
#include "Bag.h"

#include "../Config/scaler.h"

// TODO: merge to bag and game manager, maybe removed
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

#endif /* SHOP_KEEPER_H */
