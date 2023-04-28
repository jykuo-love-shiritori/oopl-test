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

    private:
        game_framework::Bittermap _sprite;
        int _health;
        Vector2f _currentMomentum;
};