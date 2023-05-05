#pragma once

#include "../Library/gameutil.h"

#include "./Bittermap.h"
#include "../Unity/Vector2.h"

class Bomb{
    public:
        /* getter */
        int getDamage() const {return _damage;}
        int getBlastRadius() const {return _blastRadius;}
        int getFuse() const {return _fuse;}
        Vector2i getPosition() const {return _position;}


        void init(int type);
        void useBomb(Vector2i playerLocation);
        void drawBomb();

    private:
        int _blastRadius;
        int _damage;
        int _fuse;
        Vector2i _position;
        game_framework::Bittermap _sprite;
};