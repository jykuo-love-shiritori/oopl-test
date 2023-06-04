#ifndef SHOP_KEEPER_H
#define SHOP_KEEPER_H

#include "./Bittermap.h"
#include "Bag.h"

#include "../Config/scaler.h"

// TODO: merge to bag and game manager, maybe removed
class ShopKeeper {
    public:
        /* game misc things */
        void init() {
            const Vector2i regularBoxSize = Vector2i(1, 1) * TILE_SIZE * SCALE_SIZE;
            
            _sprite.LoadBitmapByString({
                "resources/Clint.bmp",
            }, RGB(255, 255, 255));
            _sprite.SetScale(1);
            _sprite.SetHitBox(regularBoxSize * 0.7);
        }
        void draw() {
            _sprite.Draw();
        }

        /*getter */
		Rect GetHitbox() const { return _sprite.GetHitbox(); }

        /* methods */
        virtual void trade(int* money, Bag* bag) = 0;
    private:
        game_framework::Bittermap _sprite;
};

#endif /* SHOP_KEEPER_H */
