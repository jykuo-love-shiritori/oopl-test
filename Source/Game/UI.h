#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"

class UI{
    public:
        void init();
        void showUI();

        /*getter*/
        game_framework::Bittermap getUIsprite();
        game_framework::Bittermap getNumberSprite();
        int getScore();
    private:
        game_framework::Bittermap _UIsprite;
        game_framework::Bittermap _moneyNumbers;
        int _score;
};