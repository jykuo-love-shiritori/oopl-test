#pragma once

#include "../Library/gameutil.h"
#include "Bittermap.h"
#include "../Unity/Vector2.h"

class Bug{
    public:
        void load();
        void init(Vector2i startLocation);
        void pursuit(Vector2i playerLocation);
        void drawBug();

        /* setter */
        void alterHealth(int damage) { _health += damage; }
        void setHit(bool isHitting) { _sprite.SetFrameIndexOfBitmap(isHitting ? 1 : 0); }

        /*getter */
        Rect GetHitbox() const { return Rect::FromTopLeft(_sprite.position, {50,50}); }
        bool isAlive() const { return _health > 0; }

    private:
        game_framework::Bittermap _sprite;
        int _health;
        Vector2f _currentMomentum;
};