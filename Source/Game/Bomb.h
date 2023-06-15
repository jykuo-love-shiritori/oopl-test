#pragma once

#include "../Library/gameutil.h"

#include "./Bittermap.h"
#include "../Unity/Vector2.h"

#include "Updatable.h"

class Bomb : public Updatable {
    public:
        /* getter */
        int getDamage() const {return _damage;}
        int getBlastRadius() const {return _blastRadius;}
        int getFuse() const {return _fuse;}
        bool isShown() const {return _sprite.isShown();}
        Vector2i getCenter() const {return _sprite.GetHitbox().getCenter();};

        void init();
        void useBomb(Vector2i playerLocation,int type);
        void Update() override;
		void drawBomb() { _sprite.Draw(); }
		void drawBigWhiteCover() { _bigWhiteCover.Show(); }

    private:
        int _blastRadius;
        int _damage;
        int _fuse;
        game_framework::Bittermap _sprite;
        game_framework::Bittermap _bigWhiteCover;
};