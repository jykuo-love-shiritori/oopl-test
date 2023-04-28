#pragma once

#include "../Library/gameutil.h"
#include "./Bittermap.h"

class UI{
    public:
        void load();
        void showUI();

        /*getter*/
        int getScore() const { return _score; }

        /*setter*/
        void alterScore(int delta);
        void setScore(int score) { _score = score; }
    private:
        game_framework::Bittermap _UIsprite;
        game_framework::Bittermap _moneyNumbers;
        unsigned int _score = 0;
};