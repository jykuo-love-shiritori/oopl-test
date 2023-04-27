#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"

class UI{
    public:
        void init();
        void showUI();

        /*getter*/
        int getScore() const;

        /*setter*/
        void alterScore(int delta);
        void setScore(int score);
    private:
        game_framework::Bittermap _UIsprite;
        game_framework::Bittermap _moneyNumbers;
        unsigned int _score;
};